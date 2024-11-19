<?php
    if (!array_key_exists("personnavn", $_POST) || $_POST["personnavn"] == NULL)
        header("Location: slekt_<?php echo $projectid ?>.php?person=" . $_POST["person"]);

    include "utils.php";
    include "constants.php";
    include "item.php";
    include "person_images_" . $projectid . ".php";
    include "slekt_provider.php";

    $pagename = "slekt_" . $projectid . ".php";
    require ("slekt_topp.php");

    if (array_key_exists("provider", $_SESSION))
        $provider = $_SESSION["provider"];
    else
    {
        $provider = new Provider();
        $_SESSION["provider"] = $provider;
    }
?>

      <!--  Body  -->
<?php
    $needle = strtolower($_POST["personnavn"]);
    echo "S&oslash;ker etter " . $needle . "<p>\n";
    $persons = $provider->get_persons();
    foreach ($persons as $person_id => $person)
    {
        $person_name = $person->get_name();
        $person_name = str_replace("<u>", "", $person_name);
        $person_name = str_replace("</u>", "", $person_name);
        if (strpos(strtolower($person_name), $needle) > -1)
            echo "<a href='slekt_" . $projectid . ".php?person=" . $person_id . "'>" . $person->get_name() . "</a><br>";
    }

    echo "<p><a href='slekt_" . $projectid . ".php?person=" . $_POST["person"] . "'>Tilbake</a>";
?>

      <!--  Body slutt -->
