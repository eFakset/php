<?php
    include "utils.inc";
    include "constants.inc";
    include "item.inc";
    include "person_images_" . $projectid . ".inc";
    include "slekt_provider.inc";

    require ("slekt_topp.php");

    $pagename = "slekt_" . $projectid . ".php";
    $favicon = "slekt.ico";
    require ("topp.php");
?>
	<td valign=top height="70%">
		<table class=anetavle width="100%">
			<tr height="100">
				<td class=anetavle width="32%">
<?php
    $father_id = $person->get_father_id();
    if ($father_id == NULL)
	    echo "&nbsp;";
    else
    	echo format_person($provider, $father_id, $pagename, HORIZONTAL);
?>
				</td>
			<td class=anetavle width="32%">
<?php
    $mother_id = $person->get_mother_id();
    if ($mother_id == NULL)
	    echo "&nbsp";
    else
    	echo format_person($provider, $mother_id, $pagename, HORIZONTAL);
?>
				</td>

                <td class=anetavle rowspan="2" width="46%" align="left" valign="top">
	                <table>
    		            <tr><th align="left">S&oslash;sken</th></tr>
<?php
    $sibling_ids = $person->get_sibling_ids();
    if ($sibling_ids == NULL)
	    echo "<tr><td>&nbsp;</td></tr>";
    else
    {
        foreach ($sibling_ids as $sibling_id => $v)
    		echo "<tr><td>" . format_person_short($provider, $sibling_id, $pagename) . "</td></tr>";
    }
?>
					</table>
				</td>
			</tr>

			<tr height="100">
				<td class=anetavle align="center" width="50%" colspan="2">
<?php

	$histreg_id = $person->get_histregid();
	if ($histreg_id)
		echo format_person($provider, $currentpersonid, $histreg_id, HORIZONTAL);
	else
		echo format_person($provider, $currentpersonid, $pagename, HORIZONTAL);
?>
				</td>
			</tr>

			<tr>
				<td class=anetavle colspan="2" width="50%" align="left" valign="top">
					<table width="100%">
						<tr><th align="left" width="75">Begivenhet</th><th align="left" width="75">Dato</th><th align="left">&nbsp;</th></tr>
<?php
    $events = $provider->get_person_events($currentpersonid);
    if ($events == NULL || count($events) == 0)
    	echo "<tr><td>&nbsp;</td><td>&nbsp;</td><td>&nbsp;</td></tr>";
    else
    {
        foreach ($events as $event_id => $event)
        {
        	$event_type = $event->get_type();
        	if ($event_type == GED_EDUCATION || $event_type == GED_OCCUPATION || $event_type == GED_NOTE || $event_type == CONST_WORK_NOTE || $event_type == "MISC")
    			continue;
    
    		echo "<tr><td>";
        	$sourceref = $event->get_sourceref();
        	if ($sourceref != "" && strpos($sourceref, "http") > -1)
        		echo " <a href='" . $sourceref . "' target='_blank' title='Kilde'>" . $provider->get_display_event_type($event_type) . "</a>";
        	else
        		echo $provider->get_display_event_type($event_type);
        	echo "</td>";
    
    		$date = $event->get_date();
    
    		if ($date)
    		{
        		$parPos = strpos($date, "(");
        		if ($parPos > -1)
        			$date = substr($date, 0, $parPos - 1);
    		}
    
    		echo "<td>" . $date . "</td>";
    		$place_id = $event->get_place();
    		if ($event_type == GED_MARRIAGE || $event_type == GED_ENGAGEMENT || $event_type == GED_DIVORCE || $event_type == GED_SEPARATION)
    		{
    			if (strpos($event_id, "N") > -1)
    				$conn_id = substr($event_id, 1);
    			else
    		  		$conn_id = "N" . $event_id;
    			$conn_event = $provider->get_event($conn_id);
    			$conn_person_id = $conn_event->get_person_id();
    			$conn_person = $provider->get_person($conn_person_id);
    		}
    
    		echo "<td>";
    		if ($place_id == NULL || $place_id < 0)
    		{
    			if ($event_type == GED_MARRIAGE || $event_type == GED_ENGAGEMENT)
    				echo "Med: <a href='slekt_" . $projectid . ".php?person=" . $conn_person_id . "'>" . $conn_person->get_name() . "</a>";
    			else if ($event_type == GED_DIVORCE || $event_type == GED_SEPARATION)
    				echo "Fra: <a href='slekt_" . $projectid . ".php?person=" . $conn_person_id . "'>" . $conn_person->get_name() . "</a>";
    			else if ($event_type == GED_EDUCATION || $event_type == GED_OCCUPATION)
    				echo "Notat her";
    			else
    				echo "&nbsp;";
    		}
    		else
    		{
    			$place = $provider->get_place($place_id);
    			echo $place->get_name();
    			if ($event_type == GED_MARRIAGE || $event_type == GED_ENGAGEMENT)
    				echo ", med: <a href='slekt_" . $projectid . ".php?person=" . $conn_person_id . "'>" . $conn_person->get_name() . "</a>";
    			else if ($event_type == GED_DIVORCE || $event_type == GED_SEPARATION)
    				echo ", fra: <a href='slekt_" . $projectid . ".php?person=" . $conn_person_id . "'>" . $conn_person->get_name() . "</a>";
    			else if ($event_type == GED_EDUCATION || $event_type == GED_OCCUPATION)
    				echo ", Notat her";
    		}
    		echo "</td></tr>";
    	}
    }
?>
	</table>
</td>
<td class=anetavle width="50%" valign="top">
<?php
	$desc_table = $provider->get_descendant_table($currentpersonid);
	echo $desc_table;
?>
</td>
</tr>
</table>

<form action="person_soek_<?php echo $projectid ?>.php" method="POST">
	<div class=anetavle>
Del av personnavn: <input type="text" name="personnavn">
<input type="hidden" value='<?php echo $currentpersonid ?>' name="person">
<input value="S&oslash;k" type="submit"><img src="images/empty.gif">
<?php echo "<a href='anetavle_" . $projectid . ".php?person=" . $currentpersonid . "'>Anetavle</a>"; ?>
</div>
</form>

</td>
<!--  Body slutt -->
</tr>
</table>
<!-- Ytre tabell slutt -->
</body>
</html>