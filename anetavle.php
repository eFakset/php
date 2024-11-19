<?php
	include "include/utils.php";
	include "include/constants.php";
	include "include/item.php";
    include "include/person_images_" . $projectid . ".php";
    include "include/slekt_provider.php";

  	require ("slekt_topp.php");

  	$ancestors = $provider->get_ancestors($currentpersonid);

  	$pagename = "anetavle_" . $projectid . ".php";
  	require ("anetavle_table.php");

         echo "<a class=anetavle href='slekt_" . $projectid . ".php?person=" . $currentpersonid . "'>Detaljer</a>" . "  "
            .  "<a class=anetavle href='anetavle_print_" . $projectid . ".php?person=" . $currentpersonid . "' target=_blank>Utskriftsvennlig</a>";

        ?>
<?php
    require ("bunn.php");
?>
