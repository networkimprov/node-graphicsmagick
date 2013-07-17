{
  'targets': [
    {
      'target_name': 'node_graphicsmagick',
      'sources': [ 
        'src/node_graphicsmagick.cc'
      ],
      'link_settings': {
        'libraries': [ '<!(GraphicsMagick++-config --libs)' ]
      },
      'ldflags': [ '<!(GraphicsMagick++-config --ldflags)' ],
      'cflags_cc': [ '<!(GraphicsMagick++-config --cppflags)', '<!(GraphicsMagick++-config --cxxflags)' ], 
    }
  ]
}
