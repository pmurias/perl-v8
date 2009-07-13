/* bridge.cc */
#include <v8.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "ppport.h"

/* harmful macro!, but, but, ... */
#undef New

#include "bridge.h"

using namespace v8;

class V8Context {
public:

    V8Context() {
        HandleScope scope;

        Handle<ObjectTemplate> global = ObjectTemplate::New();
        Handle<Context> context = Context::New(NULL, global);

        context_ = Persistent<Context>::New(context);
    };

    virtual ~V8Context() {
        context_.Dispose();
    };

    Handle<Context> context() { return context_; };

private:
    Persistent<Context> context_;
};

V8CONTEXT *
create_v8context(void)
{
    return new V8Context();
}

void
release_v8context(V8CONTEXT *ctx)
{
    V8Context *context = static_cast<V8Context *>(ctx);

    delete context;
}

static SV *
_convert_v8value_to_sv(Handle<Value> value)
{
    if (0) ;
    else if (value->IsUndefined()) 
        return &PL_sv_undef;
    else if (value->IsNull())
        return &PL_sv_undef;
    else if (value->IsInt32())
        return newSViv(value->Int32Value());
    else if (value->IsBoolean())
        return newSVuv(value->Uint32Value());
    else if (value->IsNumber())
        return newSVnv(value->NumberValue());
    else if (value->IsString())
        return newSVpv(*(String::AsciiValue(value)), 0);
    else {
        Perl_warn(aTHX_ "Unsupported value type");
        return &PL_sv_undef;
    }
}

static Handle<Value>
_convert_sv_to_v8value(SV *sv)
{
    HandleScope scope;

    if (0) ;
    else if (SvIOK_UV(sv))
        return Uint32::New(SvUV(sv));
    else if (SvIOK(sv))
        return Integer::New(SvIV(sv));
    else if (SvNOK(sv))
        return Number::New(SvNV(sv));
    else if (SvPOK(sv))
        return String::New(SvPV_nolen(sv));

    return Undefined();
}

static Handle<Value>
_perl_method_by_name(const Arguments &args)
{
    dSP;
    int count;
    Handle<Value> result = Undefined();
    char ** arguments;

    ENTER;
    SAVETMPS;

    String::AsciiValue method(args.Data()->ToString());
    if (0) Perl_warn(aTHX_ "method called: %s", *method);

    arguments = new char *[args.Length() + 1];
    for (int i = 0; i < args.Length(); i ++) {
        String::AsciiValue str(args[i]);
        arguments[i] = savepv(*str);
    }
    arguments[args.Length()] = NULL;

    count = call_argv(*method, G_SCALAR, arguments);

    for (int i = 0; i < args.Length(); i ++) {
        Safefree(arguments[i]);
    }
    delete arguments;

    SPAGAIN;

    if (count >= 1) {
        result = _convert_sv_to_v8value(POPs);
    }

    PUTBACK;
    FREETMPS;
    LEAVE;

    return result;
}

void
v8context_register_method_by_name(V8CONTEXT *ctx, const char *method)
{
    V8Context *context = static_cast<V8Context *>(ctx);
    HandleScope scope;
    TryCatch try_catch;

    Context::Scope context_scope(context->context());

    context->context()->Global()->Set(
        String::New(method),
        FunctionTemplate::New(_perl_method_by_name,
                              String::New(method))->GetFunction()
    );
}

SV *
v8context_execute(V8CONTEXT *ctx, const char *source)
{
    V8Context *context = static_cast<V8Context *>(ctx);
    HandleScope scope;
    TryCatch try_catch;

    Context::Scope context_scope(context->context());

    Handle<Script> script
        = Script::Compile(String::New(source), Undefined());
    if (script.IsEmpty()) {
        String::AsciiValue error(try_catch.Exception());
        Perl_croak(aTHX_ "execute(): compile error: %s", *error);
        return &PL_sv_undef;
    }
    else {
        Handle<Value> result = script->Run();
        if (result.IsEmpty()) {
            String::AsciiValue error(try_catch.Exception());
            Perl_croak(aTHX_ "execute(): execute error: %s", *error);
            return &PL_sv_undef;
        }
        else {
            return _convert_v8value_to_sv(result);
        }
    }
    /* NOTREACHED */
}

