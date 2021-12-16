
def can_build(env, platform):
    return not env['production'] and env["feature_multiplethreads_allowed"]


def configure(env):
    pass
