<?php
  include "utils.inc";
  include "constants.inc";
  include "item.inc";
  include "person_images_" . $projectid . ".inc";
  include "slekt_provider.inc";

  require ("slekt_topp.php");

  $ancestors = $provider->get_ancestors($currentpersonid);
  $pagename = "anetavle_print_" . $projectid . ".php";
?>
<!DOCTYPE html>
<head>
      <title><?php echo $title; ?></title>
      <link rel="stylesheet" type="text/css" href="css/anetavle_print.css">
</head>

  <table width="100%">
<?php
  echo "<tr>";
  require ("anetavle_table.php");
?>
      </td>
      <!--  Body slutt -->
    </tr>
  </table>

