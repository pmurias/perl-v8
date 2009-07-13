/* bridge.h */

#ifdef __cplusplus
extern "C" {
#endif

typedef void V8CONTEXT;

V8CONTEXT * create_v8context(void);
void release_v8context(V8CONTEXT *ctx);
void v8context_register_method_by_name(V8CONTEXT *ctx, const char *method);
SV * v8context_execute(V8CONTEXT *ctx, const char *source);

#ifdef __cplusplus
}
#endif
