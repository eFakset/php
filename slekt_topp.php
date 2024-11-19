<!DOCTYPE html>
<head>
<?php
    $useragent=$_SERVER['HTTP_USER_AGENT'];
    $iswindows = strpos($useragent,"Windows") > -1;
    echo "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>";
?>
<title><?php echo $title; ?></title>
<link rel="stylesheet" type="text/css" href="css/basic.css">
<link rel="shortcut icon" type="image/x-icon" href=<?php echo "/icons/slekt.ico"?>>
<?php
if (!$iswindows)
{
?>
	<link rel="stylesheet" type="text/css" href="css/android.css">
<?php
}
?>
	<script language="JavaScript" src="tree.js"></script>
	<script language="JavaScript" src="tree_items.js"></script>
	<script language="JavaScript" src="tree_tpl.js"></script>
</head>

<body leftMargin=0 topMargin=0 Marginheight="0" Marginwidth="0">

<?php
    $provider = new Provider($projectid, $gedfile);

	$result = FALSE;
	if (isset($_GET["person"]))
	{
		$currentpersonid = $_GET["person"];
		$result = setcookie("last_person_id", $currentpersonid, time()+60*60*24*30);
	}
	else
	{
		if (array_key_exists("last_person_id", $_COOKIE))
			$currentpersonid = $_COOKIE["last_person_id"];
		else
			$currentpersonid = 1;
	}
	$person = $provider->get_person($currentpersonid);
	if ($person == null)
		$person = $provider->get_person(1);
?>