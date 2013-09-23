#!/usr/bin/env python
import subprocess
import os

tophi = -10.0
toplo = 3.0
btmhi = -3.0
btmlo = 10.0
N = 60
variants = {
  'green':  '#00A020',
  'red':    '#FF0000',
  'orange': '#FFA000',
  'blue':   '#0000FF',
}
sizes = [16, 20, 22, 24, 32, 36, 48, 64, 72, 96, 128, 192, 256, 512]

ICON = '''<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<svg
   xmlns:svg="http://www.w3.org/2000/svg"
   xmlns="http://www.w3.org/2000/svg"
   width="400"
   height="400"
   id="svg2"
   version="1.1">
    {0}

   <!-- g transform="matrix(1.25,0,0,-1.25,0,39.999951)" id="g10" //-->
   <g transform="translate(260,161)" id="g12">
   <g transform="scale({1},{1})" id="text14">
     <path
       d="m -20.161007,6.8288 0.856818,0 0,-2.89924 
          c   0,-0.14944 0.01993,-0.30885 0.06974,-0.42841 0.139482,-0.43837 0.547966,-0.87674 1.085967,-0.87674 0.667521,0 1.006263,0.54797 
              1.006263,1.31512 
          l   0,2.88927 0.856818,0 0,-2.97894 
          c   0,-0.15941 0.02989,-0.30885 0.06974,-0.43837 0.159408,-0.41845 0.538003,-0.78708 1.046116,-0.78708 0.697409,0 1.046115,0.54797 
              1.046115,1.48449 
          l   0,2.7199 0.856818,0 0,-2.8295 
          c   0,-1.67378 -0.946486,-2.09223 -1.59408,-2.09223 -0.458298,0 -0.767152,0.11956 -1.056079,0.33875 -0.199259,0.14944 -0.39852,0.3487 
             -0.547965,0.62767 
          l  -0.01993,0 
          c  -0.209222,-0.5679 -0.707373,-0.96642 -1.354968,-0.96642 -0.807002,0 -1.255338,0.42841 -1.524339,0.88671 
          l  -0.02989,0 -0.03985,-0.78708 -0.767151,0 
          c   0.01993,0.39852 0.03985,0.79704 0.03985,1.30516 
          l   0,3.51694 z"
       id="path3019"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:#ffffff" />
     <path
       d="m  -7.308739,5.92216 
          c  -0.348705,0.16937 -0.886708,0.27897 -1.424709,0.27897 -1.623968,0 -2.570454,-1.04612 -2.570454,-2.69998 0,-1.76345 1.046116,-2.76971 
              2.620269,-2.76971 0.557927,0 1.026189,0.11956 1.345005,0.27896 
          l   0.219186,-0.70737 
          c  -0.229149,-0.11955 
             -0.767152,-0.29889 -1.59408,-0.29889 -2.082265,0 -3.506976,1.41475 -3.506976,3.5269 0,2.21179 1.414748,3.40735 3.307716,3.40735 
              0.816965,0 1.464561,-0.15941 1.773414,-0.31882 
          l  -0.169371,-0.69741 z"
       id="path3021"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:#ffffff" />
     <path
       d="m  -6.043437,6.8288 0.866781,0 0,-2.9092 0.816966,0 
          c   0.787076,0.0299 1.155708,0.3786 1.354968,1.30515 0.179334,0.83689 0.328779,1.40479 0.438372,1.60405 
          l   0.89667,0 
          c  -0.139482,-0.25904 -0.29889,-0.90664 -0.518076,-1.84316 -0.159408,-0.69741 -0.468261,-1.17563 -0.976374,-1.35497 
          l   0,-0.0299 
          c   0.69741,-0.23911 1.255338,-0.82693 1.255338,-1.70367 0,-0.52804 -0.19926,-0.98634 -0.528039,-1.28523 -0.408482,-0.36863 -1.016227,-0.54796 
             -1.942785,-0.54796 -0.587816,0 -1.225449,0.0598 -1.663821,0.13948 
          l   0,6.6254 z
          m   0.866781,-6.01766 
          c   0.149445,-0.0399 0.438373,-0.0697 0.856818,-0.0697 0.916595,0 1.544265,0.3786 1.544265,1.24538 0,0.76715 -0.587818,1.27526 -1.514376,1.27526
          l  -0.886707,0 0,-2.4509 z"
       id="path3023"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:#ffffff" />
     <path
       d="m  -0.693304,6.8288 3.746088,0 0,-0.7273 -2.869344,0 0,-5.98777 -0.876744,0 0,6.71507 z"
       id="path3025"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:#ffffff" />
     <path
       d="m   8.135089,6.8288 0,-0.69741 -1.803303,0 
          c  -0.259038,0 -0.567891,0.01 -0.816966,0.0399 
          l   0,-0.0299 0.508113,-0.36863 
          c   1.046114,-0.73726 1.763451,-1.42471 1.763451,-2.35127 0,-0.98634 -0.717337,-1.55423 -1.723599,-1.55423 -0.807002,0 -1.454598,0.34871 
             -1.813266,0.61771 
          l   0.239112,0.56789 
          c   0.338742,-0.24908 0.836892,-0.48819 1.345005,-0.48819 0.627668,0 1.076004,0.32878 1.076004,0.97638 0,0.807 -0.737264,1.48448 
             -2.231712,2.47082 
          l  -0.488187,0.33874 0,0.47823 3.945348,0 z"
       id="path3027"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:#ffffff" />

     <path
       d="m -20.161007,6.8288 0.856818,0 0,-2.89924 
          c   0,-0.14944 0.01993,-0.30885 0.06974,-0.42841 0.139482,-0.43837 0.547966,-0.87674 1.085967,-0.87674 0.667521,0 1.006263,0.54797 
              1.006263,1.31512 
          l   0,2.88927 0.856818,0 0,-2.97894 
          c   0,-0.15941 0.02989,-0.30885 0.06974,-0.43837 0.159408,-0.41845 0.538003,-0.78708 1.046116,-0.78708 0.697409,0 1.046115,0.54797 
              1.046115,1.48449 
          l   0,2.7199 0.856818,0 0,-2.8295 
          c   0,-1.67378 -0.946486,-2.09223 -1.59408,-2.09223 -0.458298,0 -0.767152,0.11956 -1.056079,0.33875 -0.199259,0.14944 -0.39852,0.3487 
             -0.547965,0.62767 
          l  -0.01993,0 
          c  -0.209222,-0.5679 -0.707373,-0.96642 -1.354968,-0.96642 -0.807002,0 -1.255338,0.42841 -1.524339,0.88671 
          l  -0.02989,0 -0.03985,-0.78708 -0.767151,0 
          c   0.01993,0.39852 0.03985,0.79704 0.03985,1.30516 
          l   0,3.51694 z"
       id="path3019"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:none" />
     <path
       d="m  -7.308739,5.92216 
          c  -0.348705,0.16937 -0.886708,0.27897 -1.424709,0.27897 -1.623968,0 -2.570454,-1.04612 -2.570454,-2.69998 0,-1.76345 1.046116,-2.76971 
              2.620269,-2.76971 0.557927,0 1.026189,0.11956 1.345005,0.27896 
          l   0.219186,-0.70737 
          c  -0.229149,-0.11955 
             -0.767152,-0.29889 -1.59408,-0.29889 -2.082265,0 -3.506976,1.41475 -3.506976,3.5269 0,2.21179 1.414748,3.40735 3.307716,3.40735 
              0.816965,0 1.464561,-0.15941 1.773414,-0.31882 
          l  -0.169371,-0.69741 z"
       id="path3021"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:none" />
     <path
       d="m  -6.043437,6.8288 0.866781,0 0,-2.9092 0.816966,0 
          c   0.787076,0.0299 1.155708,0.3786 1.354968,1.30515 0.179334,0.83689 0.328779,1.40479 0.438372,1.60405 
          l   0.89667,0 
          c  -0.139482,-0.25904 -0.29889,-0.90664 -0.518076,-1.84316 -0.159408,-0.69741 -0.468261,-1.17563 -0.976374,-1.35497 
          l   0,-0.0299 
          c   0.69741,-0.23911 1.255338,-0.82693 1.255338,-1.70367 0,-0.52804 -0.19926,-0.98634 -0.528039,-1.28523 -0.408482,-0.36863 -1.016227,-0.54796 
             -1.942785,-0.54796 -0.587816,0 -1.225449,0.0598 -1.663821,0.13948 
          l   0,6.6254 
          m   0.866781,-6.01766 
          c   0.149445,-0.0399 0.438373,-0.0697 0.856818,-0.0697 0.916595,0 1.544265,0.3786 1.544265,1.24538 0,0.76715 -0.587818,1.27526 -1.514376,1.27526
          l  -0.886707,0 0,-2.4509 z"
       id="path3023"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:none" />
     <path
       d="m  -0.693304,6.8288 3.746088,0 0,-0.7273 -2.869344,0 0,-5.98777 -0.876744,0 0,6.71507 z"
       id="path3025"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:none" />
     <path
       d="m   8.135089,6.8288 0,-0.69741 -1.803303,0 
          c  -0.259038,0 -0.567891,0.01 -0.816966,0.0399 
          l   0,-0.0299 0.508113,-0.36863 
          c   1.046114,-0.73726 1.763451,-1.42471 1.763451,-2.35127 0,-0.98634 -0.717337,-1.55423 -1.723599,-1.55423 -0.807002,0 -1.454598,0.34871 
             -1.813266,0.61771 
          l   0.239112,0.56789 
          c   0.338742,-0.24908 0.836892,-0.48819 1.345005,-0.48819 0.627668,0 1.076004,0.32878 1.076004,0.97638 0,0.807 -0.737264,1.48448 
             -2.231712,2.47082 
          l  -0.488187,0.33874 0,0.47823 3.945348,0 z"
       id="path3027"
       style="fill:#000000;fill-opacity:1;fill-rule:nonzero;stroke:none" />
  </g>
  </g>
  <!-- /g //-->
</svg>
'''

PATH = '''<path style="fill:{7};fill-opacity:{6};stroke-opacity:0" transform="scale(10)"
       d="m 0,20 
          c  0 0    5   {0}  10  {0}
             5 0    15  {1}  20  {1}
             5 0    10  {2}  10  {2}
             0 0   -5   {3} -10  {3}
            -5 0   -15  {4} -20  {4}
            -5 0   -10  {5} -10  {5}
          z" />
'''

hicolordir = os.path.join('icons', 'hicolor')
if not os.path.exists(hicolordir):
  os.makedirs(hicolordir)

for name, C in variants.iteritems():
  svgname = os.path.join('icons', 'mcrl2-{0}.svg'.format(name))
  iconame = os.path.join('icons', 'mcrl2-{0}.ico'.format(name))
  icnsname = os.path.join('icons', 'mcrl2-{0}.icns'.format(name))
  pngfiles = []
  icnsfiles = []
  for size in sizes:
    iconpath = os.path.join(hicolordir, '{0}x{0}'.format(size), 'apps')
    if not os.path.exists(iconpath):
      os.mkdir(iconpath)
    pngname = os.path.join(iconpath, 'mcrl2-{0}.png'.format(name))
    xpmname = os.path.join(iconpath, 'mcrl2-{0}.xpm'.format(name))
    lo = btmlo
    hi = btmhi
    d = (btmlo - toplo) / N
    p = ''
    for i in range(0, N):
      p += PATH.format(tophi, toplo-tophi, -toplo, lo, hi - lo, -hi, 0.8 / N, C)
      lo -= d
      hi -= d
    if size <= 22:
      scale = 0
    else:
      scale = 12.0 - 2 * size / 512.0
    open(svgname, 'w+').write(ICON.format(p, scale))
    subprocess.call(['inkscape', '-z', '-e', pngname, 
                     '-w', str(size), '-h', str(size), svgname])
    # subprocess.call(['convert', pngname, xpmname])
    pngfiles.append(pngname)
    if size in [16, 32, 48, 128, 256, 512]:
      icnsfiles.append(pngname)
  subprocess.call(['convert', '-background', 'none'] + pngfiles + [iconame])
  subprocess.call(['png2icns', icnsname] + icnsfiles)

