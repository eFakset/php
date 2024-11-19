<!DOCTYPE html>

<?php
    $name = "";
    foreach ($_POST as $argument => $value)
    {
        if ($argument == "personname")
            $name = $value;
    }
    if ($name == null)
        $name = "Verden";

    $title = "Hallo fra PHP";
    $text = "Hallo " . $name . "!";
?>

<head>
    <title><?php echo $title; ?></title>
</head>
<body>
    <form action="hello.php" method="POST">
        <input name="personname" id="personname" value=<?php echo $name; ?>>
    </form>
    <?php echo $text; ?>
</body>