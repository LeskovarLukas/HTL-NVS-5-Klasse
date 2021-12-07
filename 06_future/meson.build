# uncomment as necessary
project('06_future', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

# CLI11: https://github.com/CLIUtils/CLI11
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

inc_dir = include_directories('include')
src = ['src/main.cpp']

executable('factoring',
           sources : src,
           include_directories : inc_dir,
           dependencies : [thread_dep]
           )
