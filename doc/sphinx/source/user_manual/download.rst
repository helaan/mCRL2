.. include:: toplevel.inc

.. The links to the release are hard coded in downloads-release.inc.
.. The nightly builds are linked in downloads-nightly.inc.

.. include:: downloads-release.inc
.. include:: downloads-nightly.inc

.. _download:

Download the latest release of mCRL2
====================================

The mCRL2 toolkit can be run on a number of different platforms. For some
platforms, precompiled binaries are available. The table below provides the
latest release of the toolset.


   +------------------------+------------------------+
   |Operating system        |Release (|release|)     |
   +========================+========================+
   |Windows                 | |bin_w64|_             |
   |                        +------------------------+
   |                        | |zip_w64|_             |
   +------------------------+------------------------+
   |Mac OS X                | |bin_osx|_             |
   +------------------------+------------------------+
   |Ubuntu                  | |bin_ppa|_             |
   +------------------------+------------------------+
   |Fedora                  | |bin_fedora64|_        |
   +------------------------+------------------------+
   |Source                  | |src_tgz|_             |
   +------------------------+------------------------+


Download a nightly build of mCRL2
=================================

Directly installable packages of the mCRL2 toolset are constructed every night.
They are available here.

   +------------------------+-------------------------+
   |Operating system        |Nightly build (|version|)|
   +========================+=========================+
   |Windows                 | |bin_w64n|_             |
   |                        +-------------------------+
   |                        | |zip_w64n|_             |
   +------------------------+-------------------------+
   |Mac OS X                | |bin_osx64n|_           |
   +------------------------+-------------------------+
   |Ubuntu                  | |bin_deb32n|_           |
   |                        +-------------------------+
   |                        | |bin_deb64n|_           |
   +------------------------+-------------------------+
   |Fedora                  | |bin_fedora64n|_        |
   +------------------------+-------------------------+
   |Source                  | |src_tgzn|_             |
   +------------------------+-------------------------+

If you are using a Linux distribution that is not listed, you may wish to try
:ref:`compiling mCRL2 yourself <build>`.


Known issues
------------

* Running LTSgraph on Windows with an NVDIA GPU might result in a crash.
  There are two workarounds for this: disabling the drawing of state and
  transition labels resolves the issue. This can be done by starting
  LTSgraph without arguments and disabling these options in the visualisation
  pane. The other option is to force LTSgraph to use the integrated Intel or
  AMD GPU, if available. This can be done using the NVIDIA control panel.



Previous releases
-----------------

Earlier versions of mCRL2 are listed in the :ref:`historic_releases` section.
