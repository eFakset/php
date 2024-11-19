<?php
    include "include/utils.php";
    include "include/constants.php";
    include "include/item.php";
    include "include/person_images_" . $projectid . ".php";
    include "include/slekt_provider.php";

    require ("slekt_topp.php");

    $ancestors = $provider->get_ancestors($currentpersonid);
    $pagename = "anetavle_print_" . $projectid . ".php";
?>
<?php
    echo "<tr>";
    require ("anetavle_table.php");
?>