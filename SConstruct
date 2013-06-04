# --- config ---

import imp

config = imp.new_module('config')
with open('config', 'r') as file:
    exec file.read() in config.__dict__

# --- targets ---

def makeTargets(base):
    debug = makeDebug(base, 'debug')
    release = makeRelease(base, 'release')

    makeTest(debug, 'test-debug')
    makeTest(release, 'test')

    Default('test')

# --- functions ---

def makeOptions():
    options = Variables()
    options.Add(EnumVariable('lib', 'library to build', 'static', allowed_values = ('static', 'shared')))
    options.Add(BoolVariable('fatal', 'stop on first error', True))
    return options

import os
import sys
def makeBaseEnvironment(opts):
    if sys.platform == 'win32':
        env = Environment(options = opts, ENV = os.environ, tools = ['mingw'])
    else:
        env = Environment(options = opts, ENV = os.environ)

    Help(opts.GenerateHelpText(env))

    # Pass termcaps along for colours and fancies
    if 'TERM' in os.environ:
        env['ENV']['TERM'] = os.environ['TERM']

    # Set compiler from environment
    if 'CXX' in os.environ:
        env['CXX'] = os.environ['CXX']

    setWarnings(env)
    setLanguage(env)

    setStructure(env)

    setLibs(env)

    setPlatformMacros(env)
    setVisibilityMacros(env)

    return env

def setWarnings(env):
    base = Split('-Wall -Wextra -Werror -pedantic-errors')
    ignored = prefix('-Wno-', config.ignoredWarnings)
    fatal = [ '-Wfatal-errors' ] if env['fatal'] else []

    env.MergeFlags(base + fatal + ignored)

def setLanguage(env):
    env.MergeFlags([ '-std=' + config.language ])
    env['LINK'] = env['CXX']

def setStructure(env):
    env.Append(CPPPATH = ['include'])
    env.Append(LIBPATH = ['lib'])
    system_headers = prefix('-isystem', config.systemHeaderPaths)
    env.MergeFlags(system_headers)

def setLibs(env):
    if len(config.systemLibs) > 0:
        env.ParseConfig('pkg-config --cflags --libs ' + ' '.join(config.systemLibs))
    env.Append(LIBS = config.otherLibs)

def setPlatformMacros(env):
    if env['PLATFORM'] == 'win32':
        macros = ['WINDOWS']
    else:
        macros = ['POSIX']
    env.Append(CPPDEFINES = projectMacroList(macros))

def setVisibilityMacros(env):
    if env['lib'] == 'static':
        macros = ['BUILD']
    if env['lib'] == 'shared':
        macros = ['BUILD', 'SHARED']
    env.Append(CPPDEFINES = projectMacroList(macros))

import os.path
def cloneLib(base, alias, cfg):
    env = base.Clone()
    env['config'] = cfg

    target = os.path.join(binDir(cfg), simpleName(config.projectName))
    env.VariantDir(objDir(cfg), '.', duplicate = 0)
    sources = getObjectTargets('src', cfg)
    if env['lib'] == 'static':
        lib = env.StaticLibrary(target, sources)
    if env['lib'] == 'shared':
        lib = env.SharedLibrary(target, sources)
    env.Alias(alias, lib)

    return env

def getObjectTargets(folder, cfg):
    return baseFiles(objDir(cfg), getFiles(folder, '*.c++'))

def makeDebug(base, alias):
    env = cloneLib(base, alias, 'debug')
    env.MergeFlags([ '-g' ])
    env.Append(CPPDEFINES = [ '_GLIBCXX_DEBUG' ])
    return env

def makeRelease(base, alias):
    env = cloneLib(base, alias, 'release')
    env.MergeFlags([ '-O3', '-flto' ])
    env.Append(CPPDEFINES = [ 'NDEBUG' ])
    env.Append(LINKFLAGS = [ '-flto' ])
    return env

def makeTest(base, alias):
    env = base.Clone()
    cfg = env['config']

    env.Append(LIBS = simpleName(config.projectName))
    env.Append(LIBPATH = binDir(cfg))

    env.Append(CPPPATH = [ 'test' ])

    target = os.path.join(binDir(cfg), 'runtest')
    sources = getObjectTargets('test', cfg)
    program = env.Program(target, sources)
    env.AlwaysBuild(env.Alias(alias, [program], target))

    return env

# --- generic utils ---

def prefix(base, items):
    return map(lambda e: base + e, items)

import re
def simpleName(s):
    s = s.strip()
    s = re.sub(r'\s+', '_', s)
    s = re.sub(r'[^a-zA-Z0-9]+', '_', s)
    return s

def macroPrefix(s):
    return simpleName(s).upper() + '_'

def projectMacroList(macros):
    return prefix(macroPrefix(config.projectName), macros)

def baseFiles(base, files):
    return map(lambda e: os.path.join(base, e), files)

def objDir(cfg):
    return os.path.join('obj', cfg)
def binDir(cfg):
    return os.path.join('bin', cfg)

import fnmatch
def getFiles(root, pattern):
    pattern = fnmatch.translate(pattern)
    for dir, dirs, files in os.walk(root):
        for f in files:
            if re.match(pattern, f):
                yield os.path.join(dir, f)

# --- hacks ---

import SCons
import types
def avoidRebuilds(flags):
    SCons.Action.ActionBase.get_contents_orig = SCons.Action.ActionBase.get_contents
    def get_contents(self, *args, **kw):
        cnt = self.get_contents_orig(*args, **kw).split()
        cnt_norebuild = " ".join(f for f in cnt if f not in flags)
        return cnt_norebuild
    SCons.Action.ActionBase.get_contents = types.MethodType(get_contents, None, SCons.Action.ActionBase)

avoidRebuilds(config.noRebuild)

# --- go! go! go! ---

makeTargets(makeBaseEnvironment(makeOptions()))

# vim:set ft=python:
