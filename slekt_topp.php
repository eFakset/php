<?php
	session_start();

    $provider = new Provider($projectid, $gedfile);
    $_SESSION["provider"] = $provider;

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
			header("Location: slekt_omlosning.php");
	}
	$person = $provider->get_person($currentpersonid);
	if ($person == null)
		$person = $provider->get_person(1);
?>