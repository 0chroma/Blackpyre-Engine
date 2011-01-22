/*
 * Blackpyre Engine
 * Copyright (c) 2010 0chroma. All rights reserved.
 * 
 * Source available under the Academic Free License
 * See LICENSE for licensing information
 */

#include <v8.h>
#include <v8/juice/ClassWrap.h>

#ifndef Scripting_h
#define Scripting_h

class Entity;
class GameObject;

class Scripting {
    public:
        Scripting();
        ~Scripting();
        void init();
        void run(const char* script);
        static Scripting *getInstance();
        
        static v8::Handle<v8::Value> func_load(const v8::Arguments& args);

        static v8::Handle<v8::Value> func_quit(const v8::Arguments& args);
        static v8::Handle<v8::Value> func_print(const v8::Arguments& args);
        
        static void callUpdateFunction(Entity* obj);
        
    private:
        static Scripting *instance;
        
        static v8::Handle<v8::Context> context;

        
        static void setupTimeFunctions(v8::Handle<v8::Object> dest);
        static void setupClasses(v8::Handle<v8::Object> dest);
        
        static v8::Handle<v8::ObjectTemplate> getObjectTemplate();
        static v8::Handle<v8::String> ReadFile(const char* name);
        static bool ExecuteString(v8::Handle<v8::String> source, v8::Handle<v8::Value> name, bool print_result, bool report_exceptions);
        static void ReportException(v8::TryCatch* try_catch);
        static const char* ToCString(const v8::String::Utf8Value& value);

};

#endif // Scripting_h
