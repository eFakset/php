<!-- Ytre tabell -->
  <table width=100% height=90% cellspacing=0 cellpadding=5>

    <tr>
      <!--  Venstre  -->
      <td width=85 valign=top>
        <table cellpadding=5>
<?php
        date_default_timezone_set('Europe/Paris');
        $now = date("H.i");
        echo "<tr><td class=punktliste>Oppdatert " . $now . "</td></tr>\n";
       ?>
        </table>
      </td>
      <!--  Venstre slutt  -->
