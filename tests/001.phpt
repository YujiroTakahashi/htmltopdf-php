--TEST--
Check if htmltopdf is loaded
--SKIPIF--
<?php
if (!extension_loaded('htmltopdf')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "htmltopdf" is available';
?>
--EXPECT--
The extension "htmltopdf" is available
