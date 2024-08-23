<?php
	include "utils.inc";
	include "constants.inc";
	include "item.inc";
    include "person_images_" . $projectid . ".inc";
    include "slekt_provider.inc";

  	require ("slekt_topp.php");

  	$ancestors = $provider->get_ancestors($currentpersonid);

  	$pagename = "anetavle_" . $projectid . ".php";
  	require ("topp.php");
  	require ("venstre.php");
  	require ("anetavle_table.php");

         echo "<a class=anetavle href='slekt_" . $projectid . ".php?person=" . $currentpersonid . "'>Detaljer</a>" . "  "
            .  "<a class=anetavle href='anetavle_print_" . $projectid . ".php?person=" . $currentpersonid . "' target=_blank>Utskriftsvennlig</a>";

        ?>
      </td>
      <!--  Body slutt -->
    </tr>
<?php
  require ("bunn.php");
?>
