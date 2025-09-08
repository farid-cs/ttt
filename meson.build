project('ttt', 'c',
  default_options: ['c_std=c23', 'werror=true', 'warning_level=3'])

inc = include_directories('external')

add_project_arguments(['-D_XOPEN_SOURCE', '-D_DEFAULT_SOURCE'], language: 'c')

ttt_src = ['ttt.c', 'core.c']
ttt_tui_src = ['ttt-tui.c', 'core.c', 'external/termbox2.c']

executable(meson.project_name(), ttt_src)
executable(meson.project_name() + '-tui', ttt_tui_src, include_directories: inc)
