#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"
#include "ppport.h"

#include "bridge.h"

MODULE = V8   PACKAGE = V8::Context

void
_bind_new_v8context(sv)
        SV *sv;
    PREINIT:
        V8CONTEXT *ctx;
    CODE:
        ctx = create_v8context();
        sv_magic(SvRV(sv), NULL, PERL_MAGIC_ext, NULL, 0);
        mg_find(SvRV(sv), PERL_MAGIC_ext)->mg_obj = (void *) ctx;

void
_destroy_v8context(ctx)
        V8CONTEXT *ctx;
    CODE:
        release_v8context(ctx);

MODULE = V8	PACKAGE = V8::Context PREFIX = v8context_

void
v8context_register_method_by_name(ctx, method)
        V8CONTEXT *ctx;
        const char *method;

SV *
v8context_execute(ctx, source)
        V8CONTEXT *ctx;
        const char *source;
