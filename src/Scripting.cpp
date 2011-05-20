/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

//NOTE: a lot of this stuff I borrowed from v8's shell sample code.

#include "Scripting.h"
#include "Global.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "Entity.h"
#include "util.h"

#include <v8-debug.h>
#include <v8/juice/ClassWrap.h>
#include <v8/juice/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>

// Some magic so we can get JS objects from our native objects
#define CLASSWRAP_BOUND_TYPE GameObject
#define CLASSWRAP_BOUND_TYPE_NAME "GameObject"
// OPTIONAL: #define CLASSWRAP_BOUND_TYPE_INHERITS BoundBaseClass
// ^^^^^ required if MyType sublcasses another bound native!
#include <v8/juice/ClassWrap_TwoWay.h>

#define CLASSWRAP_BOUND_TYPE Entity
#define CLASSWRAP_BOUND_TYPE_NAME "Entity"
#define CLASSWRAP_BOUND_TYPE_INHERITS GameObject
#include <v8/juice/ClassWrap_TwoWay.h>

Scripting *Scripting::instance = 0;
v8::Handle<v8::Context> Scripting::context;

Scripting::Scripting(){

}

Scripting::~Scripting(){
    v8::V8::Dispose();
}

void Scripting::init(){
    fprintf(stderr, "Scripting: Initiating scripting environment...\n");
    v8::Locker threadlockerkludge; // See http://code.google.com/p/v8/issues/detail?id=471
    v8::HandleScope handle_scope;
    
    //for time.h
    v8::Locker tlocker;

    // Get the template for the global object.
    v8::Handle<v8::ObjectTemplate> global = getObjectTemplate();
    
    // Create a new execution environment containing the built-in
    // functions
    context = v8::Context::New(NULL, global);

    // Enter the newly created execution environment.
    v8::Context::Scope context_scope(context);

    setupTimeFunctions(context->Global());
    setupClasses(context->Global());
    
    fprintf(stderr, "Scripting: Environment initialized!\n");
}

void Scripting::run(const char* script){
    v8::Locker tlock;
    v8::HandleScope handle_scope;
    v8::Context::Scope context_scope(context);
    v8::Handle<v8::String> file_name = v8::String::New(script);
    v8::Handle<v8::String> source = ReadFile(script);

    if (source.IsEmpty()) {
        fprintf(stderr, "Scripting: Error reading '%s'\n", script);
        return;
    }
    if (!ExecuteString(source, file_name, false, true)){
        fprintf(stderr, "Scripting: Problem executing '%s'\n", script);
        return;
    }
}

Scripting *Scripting::getInstance(){ 
	if(!instance){
		Scripting::instance = new Scripting;
	}
	return Scripting::instance;
}

v8::Handle<v8::ObjectTemplate> Scripting::getObjectTemplate(){
    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();

    // Bind the global 'load' function to the C++ Load callback.
    global->Set(v8::String::New("load"), v8::FunctionTemplate::New(func_load));
    // Bind the 'quit' function
    global->Set(v8::String::New("quit"), v8::FunctionTemplate::New(func_quit));
    // Bind the global 'print' function to the C++ Print callback.
    global->Set(v8::String::New("print"), v8::FunctionTemplate::New(func_print));
    //global->Set(v8::String::New("createEntity"), v8::FunctionTemplate::New(func_createEntity));
    

    return global;
}

void Scripting::callUpdateFunction(Entity* obj){ //TODO: eventually I might want to use templates or something to make sure this can be done for both Entity and ObjectFrame
    v8::Locker tlock;
    v8::HandleScope handle_scope;
    v8::TryCatch try_catch;
    namespace cv = ::v8::juice::convert;

    v8::Handle<v8::Object> jsObj = v8::Handle<v8::Object>::Cast(cv::CastToJS(obj));

    v8::Local<v8::Value>  func = jsObj->Get(v8::String::New("onUpdate"));
    if (func->IsFunction()){ //&& !func->isEmpty()){
        v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(func);
        v8::Handle<v8::Value> result = f->Call(jsObj, 0, 0);
        if(result.IsEmpty()) {
            fprintf(stderr, "Scripting: Problem when calling an entity's update function!\n");
            ReportException(&try_catch);
        }
    }
}

//Scripting::KEY_DOWN = 1;
//Scripting::KEY_UP = 2;
//Scripting::MODE_KEY = 1;
//Scripting::MODE_CHAR = 2;

void Scripting::callKeypressEvent(char key, int state, int mode){
    v8::Locker tlock;
    v8::HandleScope handle_scope;
    v8::Context::Scope context_scope(context);
    v8::TryCatch try_catch;
    
    v8::Handle<v8::Object> global = context->Global();
    
    v8::Local<v8::Value>  func = global->Get(v8::String::New(state == KEY_DOWN ? "onKeyDown" : "onKeyUp"));
    if (func->IsFunction()){ //&& !func->isEmpty()){
        v8::Local<v8::Function> f = v8::Local<v8::Function>::Cast(func);
        
        v8::Handle<v8::Value> args[] = {v8::Number::New(0), v8::Number::New(0)};
        
        if(mode == MODE_KEY)
            args[1] = v8::Number::New(key);
        else
            args[0] = v8::Number::New(key);
        
        v8::Handle<v8::Value> result = f->Call(context->Global(), 2, args);
        if(result.IsEmpty()) {
            fprintf(stderr, "Scripting: Problem when calling onKeyPress!\n");
            ReportException(&try_catch);
        }
    }
}

// ======== Setup v8 juice's bindable functions ========

void Scripting::setupTimeFunctions(v8::Handle<v8::Object> dest){ 
    dest->Set(v8::String::New("setTimeout"),
                  v8::FunctionTemplate::New( v8::juice::setTimeout )->GetFunction() );
    dest->Set(v8::String::New("clearTimeout"),
                  v8::FunctionTemplate::New( v8::juice::clearTimeout )->GetFunction() );
    dest->Set(v8::String::New("setInterval"),
                  v8::FunctionTemplate::New( v8::juice::setInterval )->GetFunction() );
    dest->Set(v8::String::New("clearInterval"),
                  v8::FunctionTemplate::New( v8::juice::clearInterval )->GetFunction() );
    dest->Set(v8::String::New("spawnTimeoutThread"),
                  v8::FunctionTemplate::New( v8::juice::spawnTimeoutThread )->GetFunction() );
    dest->Set(v8::String::New("clearTimeoutThread"),
                  v8::FunctionTemplate::New( v8::juice::clearTimeoutThread )->GetFunction() );
    dest->Set(v8::String::New("spawnIntervalThread"),
                  v8::FunctionTemplate::New( v8::juice::spawnIntervalThread )->GetFunction() );
    dest->Set(v8::String::New("clearIntervalThread"),
                  v8::FunctionTemplate::New( v8::juice::clearIntervalThread )->GetFunction() );
    dest->Set(v8::String::New("sleep"),
                  v8::FunctionTemplate::New( v8::juice::sleep )->GetFunction() );
    dest->Set(v8::String::New("mssleep"),
                  v8::FunctionTemplate::New( v8::juice::mssleep )->GetFunction() );
    dest->Set(v8::String::New("usleep"),
                  v8::FunctionTemplate::New( v8::juice::usleep )->GetFunction() );
}

// ======== Object Template Constructors for GameObject and friends ========

void Scripting::setupClasses(v8::Handle<v8::Object> dest){
    using namespace v8;
    using namespace v8::juice;
    HandleScope scope;

    // ======== GameObject ========
    typedef cw::ClassWrap<GameObject> CW;
    CW & gocw( CW::Instance() );
   
    gocw.BindMemVar<float, &GameObject::posX>( "posX" );
    gocw.BindMemVar<float, &GameObject::posY>( "posY" );
    gocw.BindMemVar<float, &GameObject::angle>( "angle" );
    gocw.BindMemVar<float, &GameObject::initialPosX>( "initialPosX" );
    gocw.BindMemVar<float, &GameObject::initialPosY>( "initialPosY" );
    gocw.BindMemVar<float, &GameObject::initialAngle>( "initialAngle" );

    typedef convert::MemFuncInvocationCallbackCreator<GameObject>
            ICM; // typing-saver
    gocw.Set( "timeSinceSpawn", ICM::M0::Invocable<uint32_t,&GameObject::timeSinceSpawn> );
    gocw.Set( "destroy", CW::DestroyObject );
    
    gocw.Seal(); // ends the binding process
    gocw.AddClassTo( dest );

    // ======== Entity ========
    typedef cw::ClassWrap<Entity> ENCW;
    ENCW & encw( ENCW::Instance() );
   
    encw.InheritNative(gocw);

    typedef convert::MemFuncInvocationCallbackCreator<Entity>
            EICM; // typing-saver
    encw.Set( "show", EICM::M0::Invocable<void,&Entity::show> );
    encw.Set( "hide", EICM::M0::Invocable<void,&Entity::hide> );

    encw.Set( "destroy", ENCW::DestroyObject );
    
    encw.Seal(); // ends the binding process
    encw.AddClassTo( dest );
}

// ======== Policy Classes for v8::Juice ========

// we need this so that we can convert floats to and from their JS natives, since Juice doesn't support it out of the box

namespace v8 { namespace juice { namespace convert {
        template <>
        struct NativeToJS<float>
        {
            v8::Handle<v8::Value> operator()( float v ) const
            {
                return Number::New( static_cast<double>(v) );
            }
        };
                                                                    
        template <>
        struct JSToNative<float>
        {
            typedef float ResultType;
            ResultType operator()( v8::Handle<v8::Value> const & h ) const
            {
                return h.IsEmpty() ? 0.0 : (h->IsNumber() ? static_cast<float>(h->NumberValue()) : 0.0);
            }
        };

        // Optional:
        static const NativeToJS<float> FloatToJS = NativeToJS<float>();
        static const JSToNative<float> JSToFloat = JSToNative<float>();

}}}

namespace v8 { namespace juice { namespace cw {
    // constructor binding
    template <>
    struct Factory<GameObject>
        : Factory_CtorForwarder<GameObject,
            tmp::TypeList<
                convert::CtorForwarder5<GameObject,float,float,float,float,float>
            >
        >
    {};
    template <>
    struct Factory<Entity>
        : Factory_CtorForwarder<Entity,
            tmp::TypeList<
                convert::CtorForwarder6<Entity,float,float,float,float,float,std::string>
            >
        >
    {};
}}}

//define JS-side name for classes
//JUICE_CLASSWRAP_CLASSNAME(Entity,"Entity")


// ======== Runtime ========

v8::Handle<v8::Value> Scripting::func_load(const v8::Arguments& args) {
    for(int i = 0; i < args.Length(); i++){
        v8::HandleScope handle_scope;
        v8::String::Utf8Value file(args[i]);
        if(*file == NULL){
            return v8::ThrowException(v8::String::New("Error loading file"));
        }
        v8::Handle<v8::String> source = ReadFile(*file);
        if(source.IsEmpty()){
            return v8::ThrowException(v8::String::New("Error loading file"));
        }
        if(!ExecuteString(source, v8::String::New(*file), false, true)){
            return v8::ThrowException(v8::String::New("Error executing file"));
        }
    }
    return v8::Undefined();
}



v8::Handle<v8::Value> Scripting::func_print(const v8::Arguments& args) {
    bool first = true;
    for(int i = 0; i < args.Length(); i++){
        v8::HandleScope handle_scope;
        if(first){
            first = false;
        }else{
            printf(" ");
        }
        v8::String::Utf8Value str(args[i]);
        const char* cstr = ToCString(str);
        printf("%s", cstr);
    }
    printf("\n");
    fflush(stdout);
    return v8::Undefined();
}

v8::Handle<v8::Value> Scripting::func_quit(const v8::Arguments& args) {
    Global *global = Global::getInstance();
    global->quitGame();
    return v8::Undefined();
}

// ================ Runtime helpers =============================

// Reads a file into a v8 string.
v8::Handle<v8::String> Scripting::ReadFile(const char* name) {
    if( !name || !*name ) {
        v8::ThrowException(v8::String::New((const char*)"Non-empty String argument required!"));
        return v8::String::New((const char*)"");
    }
    FILE* file = fopen(dataPath(name), "rb");
    if (file == NULL){
        v8::ThrowException(v8::String::New((const char*)"Could not open file."));
        return v8::String::New((const char*)"");
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    rewind(file);

    char* chars = new char[size + 1];
    chars[size] = '\0';
    for(int i = 0; i < size;){
        int read = fread(&chars[i], 1, size - i, file);
        i += read;
    }
    fclose(file);
    v8::Handle<v8::String> result = v8::String::New(chars, size);
    delete[] chars;
    return result;
}

bool Scripting::ExecuteString(v8::Handle<v8::String> source, v8::Handle<v8::Value> name, bool print_result, bool report_exceptions){
    v8::HandleScope handle_scope;
    v8::TryCatch try_catch;
    v8::Handle<v8::Script> script = v8::Script::Compile(source, name);

    if(script.IsEmpty()){
        // Print errors that happened during compilation.
        if(report_exceptions)
            ReportException(&try_catch);
        return false;
    }else{
        v8::Handle<v8::Value> result = script->Run();
        if(result.IsEmpty()){
            // Print errors that happened during execution.
            if(report_exceptions)
                ReportException(&try_catch);
            return false;
        }else{
            if(print_result && !result->IsUndefined()){
                // If all went well and the result wasn't undefined then print
                // the returned value.
                v8::String::Utf8Value str(result);
                const char* cstr = ToCString(str);
                printf("%s\n", cstr);
            }
            return true;
        }
    }
}

void Scripting::ReportException(v8::TryCatch* try_catch) {
    v8::HandleScope handle_scope;
    v8::String::Utf8Value exception(try_catch->Exception());
    const char* exception_string = ToCString(exception);
    v8::Handle<v8::Message> message = try_catch->Message();
    if(message.IsEmpty()){
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        printf("%s\n", exception_string);
    }else{
        // Print (filename):(line number): (message).
        v8::String::Utf8Value filename(message->GetScriptResourceName());
        const char* filename_string = ToCString(filename);
        int linenum = message->GetLineNumber();
        printf("%s:%i: %s\n", filename_string, linenum, exception_string);
        // Print line of source code.
        v8::String::Utf8Value sourceline(message->GetSourceLine());
        const char* sourceline_string = ToCString(sourceline);
        printf("%s\n", sourceline_string);
        // Print wavy underline (GetUnderline is deprecated).
        int start = message->GetStartColumn();
        for(int i = 0; i < start; i++){
            printf(" ");
        }
        int end = message->GetEndColumn();
        for(int i = start; i < end; i++){
            printf("^");
        }
        printf("\n");
        v8::String::Utf8Value stack_trace(try_catch->StackTrace());
        if(stack_trace.length() > 0){
            const char* stack_trace_string = ToCString(stack_trace);
            printf("%s\n", stack_trace_string);
        }
    }
}

// Extracts a C string from a V8 Utf8Value.
const char* Scripting::ToCString(const v8::String::Utf8Value& value){
    return *value ? *value : "<string conversion failed>";
}
