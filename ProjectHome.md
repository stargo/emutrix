This is a basic matrix-style mixer for [EMU1010 based cards](http://www.emu.com/products/welcome.asp?category=505&) produced by Creative Labs.

This software works under the Linux operating system, using the Advanced Linux Sound Architecture, or ALSA. "EMutrix" is a contraction of "E-MU" and "Matrix", read as "E-Mu tricks".

## News ##

**I don't have an EMU card anymore**, so won't be maintaining or improving this software. You can still download the [latest version](http://code.google.com/p/emutrix/downloads/detail?name=emutrix0.3.1.tar.gz) (0.3.1), which, while basic, could prove useful.

  * _October 14, 2010_: EMutrix version 0.2 released. Includes bug fixes, L/R channel "linking", basic support for 0404 PCI, code clean-up, and visibility options for different cards. [Download page](http://code.google.com/p/emutrix/downloads/detail?name=emutrix0.2.tar.gz).
  * _September 3, 2010_: EMutrix version 0.1 released. [Download page](http://code.google.com/p/emutrix/downloads/detail?name=emutrix0.1.tar.gz).

## Supported Cards ##
<table border='0'>
<tr valign='top'>
<td>
<h3>Tested</h3>
<ul><li><b>E-MU 1010</b>
</li><li><b>E-MU 1616M PCI</b>
</li><li><b>E-MU 1212M PCI V1</b>
</li><li><b>E-MU 0404 PCI</b>
</td>
<td>
<h3>Supported but not yet tested</h3>
</li><li><a href='http://www.emu.com/products/product.asp?category=505&subcategory=491&product=9872'>E-MU 1212M PCI V2</a>
</li><li><a href='http://www.emu.com/products/product.asp?category=505&subcategory=491&product=19169'>E-MU 1212M PCIe</a>
</li><li>E-MU 1616 PCI<br>
</li><li><a href='http://www.emu.com/products/product.asp?category=505&subcategory=491&product=19007'>E-MU 1616M PCIe</a>
</li><li>E-MU 1820 PCI<br>
</li><li>E-MU 1820M PCI<br>
</td>
<td>
<h3>Not supported</h3>
</li><li>Other cards by Creative Labs.<br>
</li></ul><blockquote>Audigy, USB interfaces, etc.</blockquote>

<ul><li>Cardbus versions <i>should</i> work.<br>
</td>
</tr><tr>
<td>
If you test one of the above, <a href='http://groups.google.com/group/emutrix'>let us know</a>.</li></ul>

<h2>Features</h2>
<ul><li>Arbitrary routing between card and ALSA inputs and outputs, also in L/R pairs<br>
</li><li>Master level<br>
</li><li>Input & output attenuation PADs<br>
</li><li>Internal clock rate<br>
For a list of planned features, see ToDo.<br>
</td><td>
<wiki:gadget url="http://www.ohloh.net/p/485088/widgets/project_factoids.xml" border="0" width="340" height="170"/><br>
</td></tr>
</table>
<h2>Installation</h2></li></ul>

A [source package](http://code.google.com/p/emutrix/downloads/detail?name=emutrix0.3.1.tar.gz) and [svn repository](http://code.google.com/p/emutrix/source/checkout) are available. Binaries may be released in the future.
You will need Qt and ALSA libraries to build the program. If you are new to Linux check out the [installation guide](InstallGuide.md) page.

<table>
<tr><td>

<h2>Contact</h2>
If you have issues you can check the now disabled <a href='http://groups.google.com/group/emutrix'>the EMutrix discussion group</a>. Also, <a href='http://code.google.com/p/emutrix/w/list'>most wiki pages</a> have a comment section.<br>
<br>
As said, <b>I am no longer maintaining this software</b>, since I don't have this hardware anymore.<br>
If someone wants to take over development, let me know.<br>
<br>
<b>Disclaimer</b>: EMutrix is in no way endorsed or supported by Creative Labs. The official mixer software produced by Creative Labs is "Patchage DSP" (Windows and Macintosh only). EMutrix software is licensed under the GNU General Public License v3.