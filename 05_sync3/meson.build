# uncomment as necessary
project('05_sync3', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')




inc_dir = include_directories('include')
src = ['src/main.cpp', 'src/philosopher.cpp']

executable('dining',
           sources : src,
           include_directories : inc_dir,
           dependencies : [thread_dep]
           )
