# -*- mode: meson -*-

# Style objective: be consistent with what mesonbuild.com documents/uses, and/or
# the meson book: https://meson-manual.com/

project(
  'mwm',
  'c',
  version: '4.23',
  default_options: [
    'c_std=c2x',
    'warning_level=1',  # enable all warnings (-Wall)
    # TODO(https://github.com/i3/i3/issues/4087): switch to
    # 'buildtype=debugoptimized',
  ],
  # Ubuntu 20.04 (supported until 2025) has meson 0.53.
  # We can revisit our minimum supported meson version
  # if it turns out to be too hard to maintain.
  meson_version: '>=0.47.0',
)

cc = meson.get_compiler('c')
add_project_arguments(cc.get_supported_arguments(['-Wunused-value']), language: 'c')

if meson.version().version_compare('>=0.48.0')
  # https://github.com/mesonbuild/meson/issues/2166#issuecomment-629696911
  meson.add_dist_script('meson/meson-dist-script')
else
  message('meson <0.48.0 detected, dist tarballs will not be filtered')
endif

################################################################################
# Version handling
################################################################################

cdata = configuration_data()

version_array = meson.project_version().split('.')
cdata.set('MAJOR_VERSION', version_array[0].to_int())
cdata.set('MINOR_VERSION', version_array[1].to_int())
if version_array.length() > 2
  cdata.set('PATCH_VERSION', version_array[2].to_int())
else
  cdata.set('PATCH_VERSION', 0)
endif
cdata.set_quoted('MWM_VERSION', '@VCS_TAG@')
cdata.set_quoted('SYSCONFDIR', join_paths(get_option('prefix'), get_option('sysconfdir')))

if get_option('b_sanitize').split(',').contains('address')
  cdata.set('I3_ASAN_ENABLED', 1)
endif

cdata.set('HAVE_STRNDUP', cc.has_function('strndup'))
cdata.set('HAVE_MKDIRP', cc.has_function('mkdirp'))

# Instead of generating config.h directly, make vcs_tag generate it so that
# @VCS_TAG@ is replaced.
config_h_in = configure_file(
  output: 'config.h.in',
  configuration: cdata,
)
config_h = declare_dependency(
  sources: vcs_tag(
    input: config_h_in,
    output: 'config.h',
    fallback: meson.project_version() + '-non-git',
  )
)

################################################################################
# docs generation
################################################################################

docdir = get_option('docdir')
if docdir == ''
  docdir = join_paths(get_option('datadir'), 'doc', 'mwm')
endif

if get_option('docs')
  asciidoc = find_program('asciidoc')
  doc_toc_inputs = [
    'docs/hacking-howto',
    'docs/userguide',
    'docs/ipc',
    'docs/multi-monitor',
    'docs/wsbar',
    'docs/testsuite',
    'docs/mwm-bar-protocol',
    'docs/mwm-bar-workspace-protocol',
    'docs/layout-saving',
  ]
  foreach m : doc_toc_inputs
    custom_target(
      m.underscorify()+'_asciidoc',
      input: m,
      output: '@BASENAME@.html',
      command: [
        asciidoc,
        '-a', 'toc',
        '-n',
        '-o', '@OUTPUT@',
        '@INPUT@',
      ],
      install: true,
      install_dir: docdir,
    )
  endforeach

  doc_notoc_inputs = [
    'docs/debugging',
  ]
  foreach m : doc_notoc_inputs
    custom_target(
      m.underscorify()+'_asciidoc',
      input: m,
      output: '@BASENAME@.html',
      command: [
        asciidoc,
        '-n',
        '-o', '@OUTPUT@',
        '@INPUT@',
      ],
      install: true,
      install_dir: docdir,
    )
  endforeach

else
  if run_command('[', '-f', 'docs/hacking-howto.html', ']', check: false).returncode() == 0
    install_data(
      [
	'docs/hacking-howto.html',
	'docs/userguide.html',
	'docs/ipc.html',
	'docs/multi-monitor.html',
	'docs/wsbar.html',
	'docs/testsuite.html',
	'docs/mwm-bar-protocol.html',
	'docs/mwm-bar-workspace-protocol.html',
	'docs/layout-saving.html',
	'docs/debugging.html',
      ],
      install_dir: docdir,
    )
  endif
endif

install_data(
  [
    'docs/bigpicture.png',
    'docs/single_terminal.png',
    'docs/snapping.png',
    'docs/two_columns.png',
    'docs/two_terminals.png',
    'docs/modes.png',
    'docs/wsbar.png',
    'docs/keyboard-layer1.png',
    'docs/keyboard-layer2.png',
    'docs/mwm-sync-working.png',
    'docs/mwm-sync.png',
    'docs/tree-layout1.png',
    'docs/tree-layout2.png',
    'docs/tree-shot1.png',
    'docs/tree-shot2.png',
    'docs/tree-shot3.png',
    'docs/tree-shot4.png',
    'docs/refcard.html',
    'docs/refcard_style.css',
    'docs/logo-30.png',
    'docs/layout-saving-1.png',
    'docs/gaps1920.png',
  ],
  install_dir: docdir,
)

if meson.version().version_compare('>=0.53')
  summary('build docs (-Ddocs)', get_option('docs'))
endif

################################################################################
# manpages
################################################################################

man1 = join_paths(get_option('mandir'), 'man1')

if get_option('mans')
  asciidoc = find_program('asciidoc')
  asciidoc_cdata = configuration_data()
  asciidoc_cdata.set('PACKAGE_VERSION', meson.project_version())
  asciidoc_conf = configure_file(
    input: 'man/asciidoc.conf.in',
    output: 'asciidoc.conf',
    configuration: asciidoc_cdata,
  )

  xmlto = find_program('xmlto')

  pod2man = find_program('pod2man')

  man_inputs = [
    'man/mwm.man',
    'man/mwm-bar.man',
    'man/mwm-msg.man',
    'man/mwm-input.man',
    'man/mwm-nagbar.man',
    'man/mwm-config-wizard.man',
    'man/mwm-sensible-editor.man',
    'man/mwm-sensible-pager.man',
    'man/mwm-sensible-terminal.man',
    'man/mwm-dump-log.man',
  ]

  foreach m : man_inputs
    xml = custom_target(
      m.underscorify()+'_asciidoc',
      input: m,
      output: '@BASENAME@.xml',
      command: [
        asciidoc,
        '-d', 'manpage',
        '-b', 'docbook',
        '-f', asciidoc_conf,
        '-o', '@OUTPUT@',
        '@INPUT@',
      ],
    )

    custom_target(
      m.underscorify()+'_xmlto',
      input: xml,
      output: '@BASENAME@.1',
      command: [
        xmlto,
        '--stringparam',
        'man.th.title.max.length=30',
        'man',
        '-o',
        '@OUTDIR@',
        '@INPUT@',
      ],
      # We should use install and install_dir instead of install_man as per:
      # https://github.com/mesonbuild/meson/issues/4981#issuecomment-467084867
      # https://github.com/mesonbuild/meson/issues/1550#issuecomment-370164307
      install: true,
      install_dir: man1,
    )
  endforeach

  pod2man_inputs = [
    'mwm-dmenu-desktop',
    'mwm-save-tree',
  ]
  foreach m : pod2man_inputs
    custom_target(
      m.underscorify()+'_pod2man',
      input: m,
      output: '@BASENAME@.1',
      command: [
        pod2man,
        '--utf8',
        '@INPUT@',
        '@OUTPUT@',
      ],
      # We should use install and install_dir instead of install_man as per:
      # https://github.com/mesonbuild/meson/issues/4981#issuecomment-467084867
      # https://github.com/mesonbuild/meson/issues/1550#issuecomment-370164307
      install: true,
      install_dir: man1,
    )
  endforeach

else
  if run_command('[', '-f', 'man/mwm.1', ']', check: false).returncode() == 0
    install_data(
      [
	'man/mwm.1',
	'man/mwm-bar.1',
	'man/mwm-msg.1',
	'man/mwm-input.1',
	'man/mwm-nagbar.1',
	'man/mwm-config-wizard.1',
	'man/mwm-sensible-editor.1',
	'man/mwm-sensible-pager.1',
	'man/mwm-sensible-terminal.1',
	'man/mwm-dump-log.1',
	'man/mwm-dmenu-desktop.1',
	'man/mwm-save-tree.1',
      ],
      install_dir: man1,
    )
  endif
endif

if meson.version().version_compare('>=0.53')
  summary('build manpages (-Dmans)', get_option('mans'))
endif

# Required for e.g. struct ucred to be defined as per unix(7).
add_project_arguments('-D_GNU_SOURCE', language: 'c')

# https://mesonbuild.com/howtox.html#add-math-library-lm-portably
m_dep = cc.find_library('m', required: false)
rt_dep = cc.find_library('rt', required: false)
iconv_dep = cc.find_library('iconv', required: false)

libsn_dep = dependency('libstartup-notification-1.0', method: 'pkg-config')
xcb_dep = dependency('xcb', method: 'pkg-config')
xcb_xkb_dep = dependency('xcb-xkb', method: 'pkg-config')
xcb_randr_dep = dependency('xcb-randr', method: 'pkg-config')
xcb_shape_dep = dependency('xcb-shape', method: 'pkg-config')
xcb_util_dep = dependency('xcb-util', method: 'pkg-config')
xcb_util_cursor_dep = dependency('xcb-cursor', method: 'pkg-config')
xcb_util_keysyms_dep = dependency('xcb-keysyms', method: 'pkg-config')
xcb_util_wm_dep = dependency('xcb-icccm', method: 'pkg-config')
xcb_util_xrm_dep = dependency('xcb-xrm', method: 'pkg-config')
xkbcommon_dep = dependency('xkbcommon', method: 'pkg-config')
xkbcommon_x11_dep = dependency('xkbcommon-x11', method: 'pkg-config')
yajl_dep = dependency('yajl', method: 'pkg-config')
libpcre_dep = dependency('libpcre2-8', version: '>=10', method: 'pkg-config')
cairo_dep = dependency('cairo', version: '>=1.14.4', method: 'pkg-config')
pangocairo_dep = dependency('pangocairo', method: 'pkg-config')
glib_dep = dependency('glib-2.0', method: 'pkg-config')
gobject_dep = dependency('gobject-2.0', method: 'pkg-config')

ev_dep = cc.find_library('ev')

inc = include_directories('include')

libmwmsrcs = [
  'libmwm/boolstr.c',
  'libmwm/create_socket.c',
  'libmwm/dpi.c',
  'libmwm/draw_util.c',
  'libmwm/fake_configure_notify.c',
  'libmwm/font.c',
  'libmwm/format_placeholders.c',
  'libmwm/get_colorpixel.c',
  'libmwm/get_config_path.c',
  'libmwm/get_exe_path.c',
  'libmwm/get_mod_mask.c',
  'libmwm/get_process_filename.c',
  'libmwm/get_visualtype.c',
  'libmwm/g_utf8_make_valid.c',
  'libmwm/ipc_connect.c',
  'libmwm/ipc_recv_message.c',
  'libmwm/ipc_send_message.c',
  'libmwm/is_debug_build.c',
  'libmwm/path_exists.c',
  'libmwm/resolve_tilde.c',
  'libmwm/root_atom_contents.c',
  'libmwm/safewrappers.c',
  'libmwm/string.c',
  'libmwm/ucs2_conversion.c',
  'libmwm/nonblock.c',
  'libmwm/screenshot_wallpaper.c',
  'libmwm/is_background_set.c',
]

if not cdata.get('HAVE_STRNDUP')
  libmwmsrcs += 'libmwm/strndup.c'
endif

if not cdata.get('HAVE_MKDIRP')
  libmwmsrcs += 'libmwm/mkdirp.c'
endif

libmwm = static_library(
  'mwm',
  libmwmsrcs,
  include_directories: inc,
  dependencies: [
    pangocairo_dep,
    config_h,
  ],
)

mwmsrcs = [
  'src/assignments.c',
  'src/bindings.c',
  'src/click.c',
  'src/commands.c',
  'src/commands_parser.c',
  'src/con.c',
  'src/config.c',
  'src/config_directives.c',
  'src/config_parser.c',
  'src/display_version.c',
  'src/drag.c',
  'src/ewmh.c',
  'src/fake_outputs.c',
  'src/floating.c',
  'src/gaps.c',
  'src/handlers.c',
  'src/ipc.c',
  'src/key_press.c',
  'src/load_layout.c',
  'src/log.c',
  'src/main.c',
  'src/manage.c',
  'src/match.c',
  'src/move.c',
  'src/output.c',
  'src/randr.c',
  'src/regex.c',
  'src/render.c',
  'src/resize.c',
  'src/restore_layout.c',
  'src/scratchpad.c',
  'src/sd-daemon.c',
  'src/sighandler.c',
  'src/startup.c',
  'src/sync.c',
  'src/tiling_drag.c',
  'src/tree.c',
  'src/util.c',
  'src/version.c',
  'src/window.c',
  'src/workspace.c',
  'src/x.c',
  'src/xcb.c',
  'src/xcursor.c',
]

# Verify the perl interpreter is present for running parser_gen,
# ensuring a good error message when it isn’t:
perl = find_program('perl')
parser_gen = find_program('generate-command-parser.pl')

command_parser = custom_target(
  'command_parser',
  input: 'parser-specs/commands.spec',
  output: [
    'GENERATED_command_enums.h',
    'GENERATED_command_tokens.h',
    'GENERATED_command_call.h',
  ],
  command: [perl, parser_gen, '--input=@INPUT@', '--prefix=command'],
)

mwmsrcs += command_parser

config_parser = custom_target(
  'config_parser',
  input: 'parser-specs/config.spec',
  output: [
    'GENERATED_config_enums.h',
    'GENERATED_config_tokens.h',
    'GENERATED_config_call.h',
  ],
  command: [parser_gen, '--input=@INPUT@', '--prefix=config'],
)

mwmsrcs += config_parser

# src/log.c uses threading primitives for synchronization
thread_dep = dependency('threads')

common_deps = [
  thread_dep,
  m_dep,
  iconv_dep,
  rt_dep,
  libsn_dep,
  xcb_dep,
  xcb_xkb_dep,
  xcb_randr_dep,
  xcb_shape_dep,
  xcb_util_dep,
  xcb_util_cursor_dep,
  xcb_util_keysyms_dep,
  xcb_util_wm_dep,
  xcb_util_xrm_dep,
  xkbcommon_dep,
  xkbcommon_x11_dep,
  yajl_dep,
  libpcre_dep,
  cairo_dep,
  pangocairo_dep,
  glib_dep,
  gobject_dep,
  ev_dep,
  config_h,
]

executable(
  'mwm',
  mwmsrcs,
  install: true,
  include_directories: inc,
  dependencies: common_deps,
  link_with: libmwm,
)

# This is the only currently working way of installing a symbolic link:
meson.add_install_script(
  'meson/meson-install-mwm-with-shmlog',
  get_option('bindir'),
)

executable(
  'mwm-bar',
  [
    'mwm-bar/src/child.c',
    'mwm-bar/src/config.c',
    'mwm-bar/src/ipc.c',
    'mwm-bar/src/main.c',
    'mwm-bar/src/mode.c',
    'mwm-bar/src/outputs.c',
    'mwm-bar/src/parse_json_header.c',
    'mwm-bar/src/workspaces.c',
    'mwm-bar/src/xcb.c',
  ],
  install: true,
  include_directories: include_directories('include', 'mwm-bar/include'),
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'mwm-config-wizard',
  [
    'mwm-config-wizard/mwm-config-wizard-atoms.xmacro.h',
    'mwm-config-wizard/main.c',
    'mwm-config-wizard/xcb.h',
    config_parser,
  ],
  install: true,
  include_directories: include_directories('include', 'mwm-config-wizard'),
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'mwm-dump-log',
  'mwm-dump-log/main.c',
  install: true,
  include_directories: inc,
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'mwm-input',
  [
    'mwm-input/mwm-input.h',
    'mwm-input/keysym2ucs.h',
    'mwm-input/keysym2ucs.c',
    'mwm-input/main.c',
  ],
  install: true,
  include_directories: inc,
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'mwm-msg',
  'mwm-msg/main.c',
  install: true,
  include_directories: inc,
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'mwm-nagbar',
  [
    'mwm-nagbar/mwm-nagbar-atoms.xmacro.h',
    'mwm-nagbar/main.c',
  ],
  install: true,
  include_directories: include_directories('include', 'mwm-nagbar'),
  dependencies: common_deps,
  link_with: libmwm,
)

install_data(
  [
    'mwm-dmenu-desktop',
    'mwm-save-tree',
    'mwm-sensible-editor',
    'mwm-sensible-pager',
    'mwm-sensible-terminal',
  ],
  install_dir: 'bin',
)

install_subdir(
  'etc',
  strip_directory: true,
  install_dir: join_paths(get_option('sysconfdir'), 'mwm'),
)

install_subdir(
  'share/',
  strip_directory: true,
  install_dir: get_option('datadir'),
)

install_headers(
  'include/mwm/ipc.h',
  subdir: 'mwm',
)

# We cannot use configure_file for complete-run.pl.in and mwmtest.pm.in
# because configure_file strips the backslash in e.g. \@display,
# resulting in @display, breaking our Perl code:
# https://github.com/mesonbuild/meson/issues/7165
bash = find_program('bash')
replace_dirs = [
  bash, '-c',  # Use bash to capture output and mark as executable
  'sed -e \'s,@abs_top_builddir@,'
  + meson.current_build_dir()
  + ',g;s,@abs_top_srcdir@,'
  + meson.current_source_dir()+',g\''
  # Only mark files ending in .pl as executables
  + ' "$0" > "$1" && { [[ "${1##*.}" == pl ]] && chmod +x "$1" || true; }',
  '@INPUT0@',   # $0
  '@OUTPUT0@',  # $1
]
complete_run = custom_target(
  'complete-run',
  input: ['testcases/complete-run.pl.in'],
  output: ['complete-run.pl'],
  command: replace_dirs,
  # build this target when running e.g. ninja or ninja test.
  # This is required for older meson versions (< 0.46.0).
  build_by_default: true,
)
mwmtest_pm = custom_target(
  'mwmtest-pm',
  input: ['testcases/lib/mwmtest.pm.in'],
  output: ['mwmtest.pm'],
  command: replace_dirs,
  # build this target when running e.g. ninja or ninja test.
  # This is required for older meson versions (< 0.46.0).
  build_by_default: true,
)

if get_option('docs')
  mwm_pod2html = find_program('docs/mwm-pod2html')

  custom_target(
    'lib-mwmtest.html',
    input: mwmtest_pm,
    output: 'lib-mwmtest.html',
    command: [
      mwm_pod2html,
      '@INPUT@',
      '@OUTPUT@',
    ],
    install: true,
    install_dir: docdir,
  )

  custom_target(
    'lib-mwmtest-test.html',
    input: 'testcases/lib/mwmtest/Test.pm',
    output: 'lib-mwmtest-test.html',
    command: [
      mwm_pod2html,
      '@INPUT@',
      '@OUTPUT@',
    ],
    install: true,
    install_dir: docdir,
  )
endif

executable(
  'test.inject_randr15',
  'testcases/inject_randr1.5.c',
  include_directories: inc,
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'test.commands_parser',
  [
    'src/commands_parser.c',
    command_parser,
  ],
  include_directories: inc,
  c_args: '-DTEST_PARSER',
  dependencies: common_deps,
  link_with: libmwm,
)

executable(
  'test.config_parser',
  [
    'src/config_parser.c',
    config_parser,
  ],
  include_directories: inc,
  c_args: '-DTEST_PARSER',
  dependencies: common_deps,
  link_with: libmwm,
)

anyevent_mwm = custom_target(
  'anyevent-mwm',
  # Should be AnyEvent-MWM/blib/lib/AnyEvent/MWM.pm,
  # but see https://github.com/mesonbuild/meson/issues/2320
  output: 'AnyEvent-MWM.stamp',
  command: [
    'sh',
    '-c',
    'cp -r @0@/AnyEvent-MWM . && cd AnyEvent-MWM && perl Makefile.PL && make && touch ../AnyEvent-MWM.stamp'.format(meson.current_source_dir()),
  ],
)

if meson.version().version_compare('>=0.46.0')
  test(
    'complete-run',
    perl,
    args: [complete_run],
    depends: [
      anyevent_mwm,
      mwmtest_pm,
    ],
    timeout: 120,  # Default of 30 seconds can cause timeouts on slower machines
  )
else
  # meson < 0.46.0 does not support the depends arg in test targets.
  # Just hope for the best.
  test(
    'complete-run',
    perl,
    args: [complete_run],
  )
  message('meson < 0.46 detected, you might need to run ninja test twice')
endif
