<h3 class=anetavle>Anetavle <?php echo $person->get_name() ?></h3>

<?php
        $image_orientation = NO_IMAGE;
        foreach ($ancestors as $ancestor_key => $ancestor)
        {
        	if (strlen($ancestor_key) == 3)
        	{
        		$person_id = $ancestor->get_id();
        		$image_info = $provider->get_person_image($person_id);
        		if (count($image_info) > 0)
                {
                    $image_orientation = VERTICAL;
                    break;
                }
        	}
        }
?>
        <table class=anetavle width="100%">
        <tr>
          <?php
            echo "\n<td class=anetavle width=12% align=center";
            if (array_key_exists("FFF", $ancestors))
            {
            	if ($image_orientation == VERTICAL)
            	    echo " valign=bottom>";
            	else
            	    echo ">";
                $ancestor = $ancestors["FFF"];
       		    echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
                echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "\n<td class=anetavle width=13% align=center";
            if (array_key_exists("FFM", $ancestors))
            {
            	if ($image_orientation == VERTICAL)
            	    echo " valign=bottom>";
            	else
            	    echo ">";
                $ancestor = $ancestors["FFM"];
                echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
                echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "\n<td class=anetavle width=12% align=center";
            if (array_key_exists("FMF", $ancestors))
            {
            	if ($image_orientation == VERTICAL)
            	  echo " valign=bottom>";
            	else
            	  echo ">";
                $ancestor = $ancestors["FMF"];
        		echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
              echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "\n<td class=anetavle width=13% align=center";
            if (array_key_exists("FMM", $ancestors))
            {
            	if ($image_orientation == VERTICAL)
            	  echo " valign=bottom>";
            	else
            	  echo ">";
              $ancestor = $ancestors["FMM"];
       		echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
              echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "<td class=anetavle width=12% align=center";
            if (array_key_exists("MFF", $ancestors))
            {
                if ($image_orientation == VERTICAL)
                    echo " valign=bottom>";
                else
                    echo ">";
                $ancestor = $ancestors["MFF"];
                echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
                echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "\n<td class=anetavle width=13% align=center";
            if (array_key_exists("MFM", $ancestors))
            {
                if ($image_orientation == VERTICAL)
                    echo " valign=bottom>";
                else
                    echo ">";
                $ancestor = $ancestors["MFM"];
                echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
                echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "\n<td class=anetavle width=12% align=center";
            if (array_key_exists("MMF", $ancestors))
            {
                if ($image_orientation == VERTICAL)
                    echo " valign=bottom>";
                else
                    echo ">";
                $ancestor = $ancestors["MMF"];
                echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
                echo ">&nbsp;";
          ?>
          </td>
          <?php
            echo "\n<td class=anetavle width=13% align=center";
            if (array_key_exists("MMM", $ancestors))
            {
                if ($image_orientation == VERTICAL)
                    echo " valign=bottom>";
                else
                    echo ">";
                $ancestor = $ancestors["MMM"];
                echo format_person($provider, $ancestor->get_id(), $pagename, $image_orientation);
            }
            else
                echo ">&nbsp;";
          ?>
          </td>
        </tr>
        <tr>
          <td class=anetavle width=25% align=center colspan="2">
          <?php
            if (array_key_exists("FF", $ancestors))
            {
                $ancestor = $ancestors["FF"];
                echo format_person($provider, $ancestor->get_id(), $pagename, HORIZONTAL);
            }
            else
                echo "&nbsp;";
          ?>
          </td>
          <td class=anetavle width=25% align=center colspan="2">
          <?php
            if (array_key_exists("FM", $ancestors))
            {
                $ancestor = $ancestors["FM"];
                echo format_person($provider, $ancestor->get_id(), $pagename, HORIZONTAL);
            }
            else
                echo "&nbsp;";
          ?>
          </td>
          <td class=anetavle width=25% align=center colspan="2">
          <?php
            if (array_key_exists("MF", $ancestors))
            {
                $ancestor = $ancestors["MF"];
                echo format_person($provider, $ancestor->get_id(), $pagename, HORIZONTAL);
            }
            else
                echo "&nbsp;";
          ?>
          </td>
          <td class=anetavle width=25% align=center colspan="2">
          <?php
            if (array_key_exists("MM", $ancestors))
            {
                $ancestor = $ancestors["MM"];
                echo format_person($provider, $ancestor->get_id(), $pagename, HORIZONTAL);
            }
            else
                echo "&nbsp;";
          ?>
          </td>
        <tr>
          <td class=anetavle width=50% align=center colspan="4">
          <?php
            if (array_key_exists("F", $ancestors))
            {
                $ancestor = $ancestors["F"];
                echo "<table><tr><td>";
                echo format_person($provider, $ancestor->get_id(), $pagename, HORIZONTAL);
                echo "</td></tr></table>";
            }
            else
                echo "&nbsp;";
          ?>
          </td>
          <td class=anetavle width=50% align=center colspan="4">
          <?php
            if (array_key_exists("M", $ancestors))
            {
                $ancestor = $ancestors["M"];
                echo "<table><tr><td>";
                echo format_person($provider, $ancestor->get_id(), $pagename, HORIZONTAL);
                echo "</td></tr></table>";
            }
            else
                echo "&nbsp;";
          ?>
          </td>
        </tr>
        <tr>
          <td class=anetavle width="100%" align="center" colspan="8">
            <table><tr><td>
            <?php
        		echo format_person($provider, $currentpersonid, $pagename, HORIZONTAL);
            ?>
            </td></tr></table>
          </td>
        </tr>
        <?php
        $child_ids = $person->get_child_ids();
        if ($child_ids != NULL)
        {
        ?>
        <tr>
          <td class=anetavle valign="top" align=center colspan="8">
            <table>
            <tr><th align="center">Barn</th></tr>
            <?php
			foreach ($child_ids as $child_id => $v)
              {
              	echo "<tr><td>";

                echo format_person_short($provider, $child_id, $pagename);

                echo "</td></tr>\n";
              }
            ?>
            </table>
        <?php
        }
        ?>
        </table>
