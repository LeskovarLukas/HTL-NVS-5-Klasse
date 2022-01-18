# uncomment as necessary
project('08_daytime', 'cpp',
        license : ['Boost'],
        version : '0.1',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

# CLI11: https://github.com/CLIUtils/CLI11
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

# ASIO
add_global_arguments('-I' + get_option('asio_include_dir'), language : 'cpp')

# SPDLOG
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

inc_dir = include_directories('include')
client_src = ['src/daytime_client/main.cpp']
server_src = ['src/daytime_server/main.cpp']

executable('daytime_client',
           sources : client_src,
           include_directories : inc_dir,
           dependencies : [thread_dep]
)

executable('daytime_server',
           sources : server_src,
           include_directories : inc_dir,
           dependencies : [thread_dep]
)
