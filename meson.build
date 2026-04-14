project('zenedit', 'cpp',
  version : '0.1',
  default_options : ['cpp_std=c++17'])

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules : ['Core', 'Gui', 'Widgets'])

# MOC is needed for classes using Q_OBJECT
processed = qt5.preprocess(
  moc_headers : 'src/zenedit.h',
)

executable('zenedit',
  ['src/main.cpp', 'src/zenedit.cpp'] + processed,
  dependencies : qt5_dep,
  install : true)
