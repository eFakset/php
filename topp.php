<!DOCTYPE html>
<head>
<?php
$useragent=$_SERVER['HTTP_USER_AGENT'];
$iswindows = strpos($useragent,"Windows") > -1;

if (isset($meta))
	echo "<meta content='" . $meta . "' name='keywords'>";

echo "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>";
?>
<title><?php echo $title; ?></title>
<link rel="stylesheet" type="text/css" href="css/basic.css">
<?php
if (!$iswindows)
{
?>
	<link rel="stylesheet" type="text/css" href="css/android.css">
	<link rel="shortcut icon" type="image/x-icon" href="/icons/slekt.ico">
<?php
}
?>
	<script language="JavaScript" src="tree.js"></script>
	<script language="JavaScript" src="tree_items.js"></script>
	<script language="JavaScript" src="tree_tpl.js"></script>
</head>

<body leftMargin=0 topMargin=0 Marginheight="0" Marginwidth="0">
<!--  Topp slutt -->
