/*
 * Blackpyre Engine
 * Copyright (c) 2010 William Riley. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

//NOTE: a lot of this stuff I borrowed from v8's shell sample code.

#include "Scripting.h"
#include "Global.h"
#include "ObjectManager.h"
#include "Entity.h"
#include "util.h"

#include <v8.h>
#include <v8/juice/ClassWrap.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

Scripting *Scripting::instance = 0;
v8::Handle<v8::Context> Scripting::context;

Scripting::Scripting(){

}

Scripting::~Scripting(){
    v8::V8::Dispose();
}

void Scripting::init(){
    fprintf(stderr, "Initiating scripting environment...\n");
    v8::HandleScope handle_scope;
    // Get the template for the global object.
    v8::Handle<v8::ObjectTemplate> global = getObjectTemplate();
    
    // Create a new execution environment containing the built-in
    // functions
    context = v8::Context::New(NULL, global);


    // Enter the newly created execution environment.
    v8::Context::Scope context_scope(context);


    Scripting::setupEntityClass(context->Global());
    fprintf(stderr, "Scripting environment initialized!\n");
}

void Scripting::run(const char* script){
    v8::HandleScope handle_scope;
    v8::Context::Scope context_scope(context);
    v8::Handle<v8::String> file_name = v8::String::New(script);
    v8::Handle<v8::String> source = ReadFile(script);
    if (source.IsEmpty()) {
        fprintf(stderr, "Error reading '%s'\n", script);
        return;
    }
    if (!ExecuteString(source, file_name, false, true)){
        fprintf(stderr, "Problem executing '%s'\n", script);
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

// ======== Object Template Constructors for Entity and friends ========

v8::Handle<v8::Object> Scripting::setupEntityClass(v8::Handle<v8::Object> dest){
    using namespace v8;
    using namespace v8::juice;
    HandleScope scope;

    typedef cw::ClassWrap<Entity> CW;
    CW & cw( CW::Instance() );
    

    cw.Set( "destroy", CW::DestroyObject );
    cw.Seal(); // ends the binding process
    cw.AddClassTo( dest ); // installs BoundNative class in dest
    return cw.CtorTemplate()->GetFunction();
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
    struct Factory<Entity>
        : Factory_CtorForwarder<Entity,
            tmp::TypeList<
                convert::CtorForwarder6<Entity,float,float,float,float,float,std::string>
            >
        >
    {};
}}}

//define JS-side name for classes
JUICE_CLASSWRAP_CLASSNAME(Entity,"Entity")


// ======== Runtime ========
/*
v8::Handle<v8::Value> Scripting::func_createEntity(const v8::Arguments& args) {
    if (args.Length() < 1) return v8::Undefined();
    v8::HandleScope handle_scope;
    v8::Handle<v8::Value> arg = args[0];
    v8::String::Utf8Value value(arg);
    float angle = atoi(ToCString(value));

    ObjectManager *objectManager = Global::getInstance()->objectManager;
    Entity *a = new Entity(300.0f, 200.0f, 100.0f, 100.0f, angle, "bullet.png"); 
    objectManager->addObject(a);

    return getEntityObjectTemplate(a);
}*/

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
        if(!ExecuteString(source, v8::String::New(*file), false, false)){
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
