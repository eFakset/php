<?php

function is_good($string)
{
  if ($string == NULL || $string == "")
    return false;
  else
    return true;
}

function format_person($provider, $person_id, $href, $image_orientation)
{
  $person = $provider->get_person($person_id);
  if (!$person)
  {
     $person_id = 1;
     $person = $provider->get_person($person_id);
  }
  $text = "";
  $image_info = array();
  if ($image_orientation != NO_IMAGE)
  {
    $image_info = $provider->get_person_image($person_id);
    $text = "<table width='100%'>";
    $text = $text . "<tr>";
    $text = $text . "  <td align='center'>";
  }

  if (substr($href, 0, 5) == "slekt" || substr($href, 0, 8) == "anetavle")
	  $text = $text . "<a href='" . $href . "?person=" . $person_id ."'>" . $person->get_name() . "</a>";
  else
	  $text = $text . "<i><a href='https://histreg.no/index.php/person/" . $href ."' target=_blank title='Lenke til Histreg.no'>" . $person->get_name() . "</a></i>";

  $birth = $person->get_birth();
  if ($birth != NULL && $birth->get_id() != NULL && $birth->get_id() != -1)
  {
  	$text = $text . "<br><img src='../images/asterix.gif'>" . $birth->get_date();
  	$birth_place = $birth->get_place();
  	if (is_good($birth_place))
  	{
  		$place = $provider->get_place($birth_place);
  	  $text = $text . ", " . $place->get_name();
  	}
  }
  $death = $person->get_death();
  if ($death != NULL && $death->get_id() != NULL && $death->get_id() != -1)
  {
  	$text = $text . "<br><img src='../images/cross.gif'>" . $death->get_date();
  	$death_place = $death->get_place();
  	if (is_good($death_place))
  	{
  		$place = $provider->get_place($death_place);
  	  $text = $text . ", " . $place->get_name();
  	}
  }

  if ($image_orientation != NO_IMAGE)
  {
    $text = $text . "  </td>";
    if ($image_orientation == VERTICAL)
    {
      $text = $text . "</tr><tr>";
    }
    if (count($image_info) > 0)
    {
      $text = $text . "  <td align='center' valign='center' width='" . $image_info[1] . "'>";
      $text = $text . "    <img src='" . $image_info[0] . "' width='" . $image_info[1] . "' height='" . $image_info[2] . "'>";
    }
    else
    {
      $text = $text . "  <td align='center' valign='center'>";
      $text = $text . "    <img src='Foto/empty.gif' height='" . MAX_IMAGE_HEIGHT . "'>";
    }
    $text = $text . "  </td>";
    $text = $text . "</tr>";
    $text = $text . "</table>";
  }
  
  return $text;
}

function format_person_short($provider, $person_id, $href)
{
	$person = $provider->get_person($person_id);


      if (substr($href, 0, 5) == "slekt" || substr($href, 0, 8) == "anetavle")
    	  $text = "<a href='" . $href . "?person=" . $person_id ."'>" . $person->get_name() . "</a>";
      else
    	  $text = "<i><a href='https://histreg.no/index.php/person/" . $href ."' target=_blank title='Lenke til Histreg.no'>" . $person->get_name() . "</a></i>";


  $birth = $person->get_birth();
  $death = $person->get_death();
  if ($birth->get_id() > -1 || $death->get_id() != NULL)
  {
  	$text = $text . " (";
    if ($birth->get_id() > -1)
    {
    	$text = $text . $birth->get_date();
    }
  	$text = $text . " - ";
    if ($death->get_id() != NULL)
    {
    	$text = $text . $death->get_date();
    }
  	$text = $text . ")";
  }
  $text = $text . "</a>";
  
  return $text;
}
?>
