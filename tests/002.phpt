--TEST--
htmltopdf() Basic test
--SKIPIF--
<?php
if (!extension_loaded('htmltopdf')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = html2pdf('https://www.yahoo.co.jp/', 'yahoo.pdf');

var_dump($ret);
?>
--EXPECT--
int(0)
