<?php

class Provider
{
	var $projectid;
  var $current_person;
  var $current_person_id;
  var $current_family_id;
  var $current_source_id;
  var $current_event;
  var $current_family;
  var $current_source;
  var $next_event_id = 1;
  var $next_place_id = 1;

  var $persons;
  var $families;
  var $events;
  var $sources;
  var $places;
  
  var $event_types;
  
  var $person_images;

  public function __construct($projectid, $gedfile)
  {
    $this->projectid = $projectid;
    $prevpersonid = "";

    $this->current_person_id = NULL;
    $this->current_family_id = NULL;
    $this->current_source_id = NULL;
    $this->current_event = new Event(NULL, "");
    $this->current_person = new Person(NULL, "");
    $this->current_family = new Family(NULL, "");
    $this->current_source = NULL;

    $this->persons = array();
    $this->families = array();
    $this->events = array();
    $this->sources = array();
    $this->places = array();

    $this->event_types = array();

    $this->event_types["WORK"] = "Arbeidsnotat";
    $this->event_types["ENGA"] = "Lysning";
    $this->event_types["NOTE"] = "Notat";
    $this->event_types["MISC"] = "Diverse";
    $this->event_types["OCCU"] = "Yrke";
    $this->event_types["BIRT"] = "F&oslash;dsel";
    $this->event_types["CHR"]  = "D&aring;p";
    $this->event_types["CENS"] = "Folketelling";
    $this->event_types["MARR"] = "Vielse";
    $this->event_types["DIV"]  = "Skilsmisse";
    $this->event_types["DIVF"] = "Separasjon";
    $this->event_types["CONF"] = "Konfirmasjon";
    $this->event_types["RESI"] = "Bosted";
    $this->event_types["BURI"] = "Begravelse";
    $this->event_types["URNE"] = "Urnenedsettelse";
    $this->event_types["DEAT"] = "D&oslash;d";
    $this->event_types["EDUC"] = "Utdannelse";
    $this->event_types["EMIG"] = "Emigrasjon";
    $this->event_types["NATU"] = "Naturalisering";

    if (!($file=fopen($gedfile,"r")))
      exit("Unable to open file.");

    $this->read_data($file);

    fclose($file);

    $this->process_families();

    $this->person_images = new PersonImages();
  }
  
  function to_string()
  {
  	return "Prosjektid: " . $this->projectid;
  }

  function get_display_event_type($event_type)
  {
  	return $this->event_types[$event_type];
  }

  function get_person($id)
  {
    return $this->persons[$id];
  }

  function get_person_image($id)
  {
  	$person_image = $this->person_images->get_person_image($id);
  	return $person_image;
  }

  function get_persons()
  {
    return $this->persons;
  }

  function read_data($file)
  {
    $line = "";

    while (!feof($file))
    {
      $this->process_line(trim(fgets($file)));
    }
  }

  function process_line($line)
  {
    $line = str_replace("æ", "&aelig;", $line);
    $line = str_replace("Æ", "&Aelig;", $line);
	$line = str_replace("ø", "&oslash;", $line);
 	$line = str_replace("Ø", "&Oslash;", $line);
	$line = str_replace("å", "&aring;", $line);
	$line = str_replace("Å", "&Aring;", $line);

    $line_type = substr($line, 0, 1);
    $ged_type = "";
    $ged_id = "";
    $ged_data = "";
    $space_pos = -1;
    if (strlen($line) > 3)
    {
      $sec_string = "";
      $space_pos = strpos($line, ' ', 3);
      if (!$space_pos)
        $sec_string = trim(substr($line, 2));
      else
        $sec_string = trim(substr($line, 2, $space_pos - 2));
      if (strpos($sec_string, "@") > -1)
      {
        $ged_id = substr($sec_string, 2, strlen($sec_string) - 3);
        if (strpos($ged_id, "I") > -1)
          $ged_id = substr($ged_id, 1);
        $ged_type = substr($line, $space_pos + 1);
      }
      else
      {
        $ged_type = $sec_string;
        if ($space_pos > -1)
        {
          $third_string = substr($line, $space_pos + 1);

          if (strpos($third_string, "@") > -1)
          {
            $ged_id = substr($third_string, 1, (strpos($third_string, "@", 1) - 1));
            if (strpos($ged_id, "I") > -1 || strpos($ged_id, "F") > -1)
              $ged_id = substr($ged_id, 1);

            if ($ged_type == "SOUR")
            {
              if (strlen($third_string) > (strpos($third_string, "@", 1) + 1))
                $ged_data = substr($third_string, strpos($third_string, "@", 1) + 1);
            }
          }
          else
            $ged_data = $third_string;
        }
      }
    }

    if ($line_type == 0)
      $this->process_start_row($ged_type, $ged_id);
    else if ($line_type == 1)
      $this->process_event_row($ged_type, $ged_id, $ged_data);
    else if ($line_type == 2)
      $this->process_detail($line, $ged_type, $ged_id, $ged_data);
    else if ($line_type == 3)
      $this->process_detail($line, $ged_type, $ged_id, $ged_data);
  }

// 0
  function process_start_row($type, $id)
  {
    if ($type == "INDI")
    {
      if ($this->current_person_id != NULL)
        $this->persons[$this->current_person->get_id()] = $this->current_person;
      $this->current_person_id = $id;
    }
    else if ($type == "FAM")
    {
      $this->current_event = NULL;  // @todo  Funker dette?
      if ($this->current_family_id != NULL)
        $this->families[$this->current_family->get_id()] = $this->current_family;
      $this->current_family_id = $id;
      $this->current_family = new Family($id, NULL);
    }
    else if ($type == GED_SOURCE)
    {
      if ($this->current_source != NULL)
        $this->sources[$this->current_source_id] = $this->current_source;
      $this->current_source_id = $id;
      $this->current_source = new Source($this->current_source_id, NULL);
    }
    else if ($type == "TRLR")
    {
      if ($this->current_person_id != NULL)
        $this->persons[$this->current_person->get_id()] = $this->current_person;
      if ($this->current_family_id != NULL)
        $this->families[$this->current_family->get_id()] = $this->current_family;
    }
  }

// 1
  function process_event_row($type, $id, $data)
  {
    if ($this->current_person_id != NULL && $type == "NAME")
      $this->current_person = new Person($this->current_person_id, $data);
    else if ($type == HISTREG_ID)
      $this->current_person->set_histregid($data);
    else if ($type == GED_SEX)
      $this->current_person->set_gender($data);
    else if ($type == ANCESTRY_CATEGORY)
      $this->current_person->set_ancestry_category($data);
    else if ($type == GED_HUSBAND)
      $this->current_family->set_husband_id($id);
    else if ($type == GED_WIFE)
      $this->current_family->set_wife_id($id);
    else if ($type == GED_CHILD)
      $this->current_family->add_child_id($id);
    else if ($this->current_source != null) // && $type == GED_TITLE)
    {
      $this->current_source->set_name($data);
    }
    else if ($this->current_family != null && $type == GED_ENGAGEMENT)
    {
      $this->next_event_id++;
      $this->current_event = new Event($this->next_event_id, $type);
      $this->current_family->set_engagement_id($this->current_event->get_id());
      $this->events[$this->next_event_id] = $this->current_event;
    }
    else if ($this->current_family != null && $type == GED_MARRIAGE)
    {
      $this->next_event_id++;
      $this->current_event = new Event($this->next_event_id, $type);
      $this->current_family->set_marriage_id($this->current_event->get_id());
      $this->events[$this->next_event_id] = $this->current_event;
    }
    else if ($this->current_family != null && $type == GED_SEPARATION)
    {
      $this->next_event_id++;
      $this->current_event = new Event($this->next_event_id, $type);
      $this->current_family->set_separation_id($this->current_event->get_id());
      $this->events[$this->next_event_id] = $this->current_event;
    }
    else if ($this->current_family != null && $type == GED_DIVORCE)
    {
      $this->next_event_id++;
      $this->current_event = new Event($this->next_event_id, $type);
      $this->current_family->set_divorce_id($this->current_event->get_id());
      $this->events[$this->next_event_id] = $this->current_event;
    }
    else if ($this->current_person_id != null)
    {
      if ($type == GED_NOTE)
      {
        if (strpos($data, "AN: ") > -1)
        {
          $type = CONST_WORK_NOTE;
          $data = substr($data, 4);
        }
      }
      $this->next_event_id++;
      $this->current_event = new Event($this->next_event_id, $type);
      $this->current_event->set_person_id($this->current_person_id);
      if ($type == GED_NOTE || $type == CONST_WORK_NOTE)
        $this->current_event->add_note($data);
      else if ($type == GED_SOURCE)
      {
        $source_len = strlen($data);
        $last_source_str = substr($data, $source_len, 1);
        if ($last_source_str == "@")
        {
          $data = substr($data, 1, $source_len-1);
        }
        else
        {
          $at_pos = strpos($data, "@");
        }
      }
      else if ($type == GED_BIRTH)
        $this->current_person->set_birth($this->current_event);
      else if ($type == GED_DEATH)
        $this->current_person->set_death($this->current_event);
      $this->events[$this->current_event->get_id()] = $this->current_event;
    }
    else
      $this->current_event = null;
  }

  function process_detail($line, $type, $id, $data)
  {
    if ($this->current_event != null)
    {
      if ($type == GED_DATE)
      {
        $this->current_event->set_date($data);
      }
      else if ($type == GED_PLACE)
      {
          $place_id = $this->next_place_id++;
          $place = new Place($place_id, $data);
          $this->places[$place_id] = $place;
          $this->current_event->set_place($place_id);
      }
      else if ($type == GED_NOTE)
      {
        $this->current_event->add_note($data);
      }
      else if ($type == GED_SOURCE)
      {
        $this->current_event->set_source($id);

        if ($data != "")
          $this->current_event->set_sourceref($data);

        if ($this->current_family != NULL)
        {
          if ($this->current_event->get_type() == GED_MARRIAGE)
            $this->current_family->set_marriage_id($this->current_event->get_id());
          else if ($this->current_event->get_type() == GED_SEPARATION)
            $this->current_family->set_separation_id($this->current_event->get_id());
          else if ($this->current_event->get_type() == GED_DIVORCE)
            $this->current_family->set_divorce_id($this->current_event->get_id());
        }
      }
      else if ($type == GED_CONTINUED || $type == GED_CONTINUED2)
      {
        $this->current_event->update_last_note($data);
      }
      else
        echo "Ukjent type: " . $type;
      if ($this->current_event->get_type() == GED_BIRTH)
        $this->current_person->set_birth($this->current_event);
      if ($this->current_event->get_type() == GED_DEATH)
        $this->current_person->set_death($this->current_event);
      $this->events[$this->current_event->get_id()] = $this->current_event;
    }
  }

  function process_families()
  {
	foreach ($this->families as $id => $family)
    {
      $husband_id = $family->get_husband_id();
      $wife_id = $family->get_wife_id();
      $child_ids = $family->get_child_ids();
      if ($husband_id == NULL)
        $husband = NULL;
      else
        $husband = $this->persons[$husband_id];
      if ($wife_id == NULL)
        $wife = NULL;
      else
        $wife = $this->persons[$wife_id];

      $children = array();
      $i = 0;
    foreach ($child_ids as $child_id => $v)
      {
      	$child = $this->persons[$child_id];
        $child->set_father_id($husband_id);
        $child->set_mother_id($wife_id);
      	$children[$child_id] = $child;
      	$this->persons[$child_id] = $child;
      	$i++;
      }

      if ($family->get_marriage_id() == NULL)
        $marriage = NULL;
      else
        $marriage = $this->events[$family->get_marriage_id()];
      if ($family->get_engagement_id() == NULL)
        $engagement = NULL;
      else
        $engagement = $this->events[$family->get_engagement_id()];
      if ($family->get_separation_id() == NULL)
        $separation = NULL;
      else
        $separation = $this->events[$family->get_separation_id()];
      if ($family->get_divorce_id() == NULL)
        $divorce = NULL;
      else
        $divorce = $this->events[$family->get_divorce_id()];

      if ($husband != NULL)
      {
        $prev_children = $husband->get_child_ids();
        if ($prev_children)
        {
         foreach ($prev_children as $prev_child_id => $v)
        {
        	reset($child_ids);
          $prev_child = $this->persons[$prev_child_id];
         foreach ($child_ids as $child_id => $v)
          {
            if ($child_id != $prev_child_id)
            {
              $this_child = $this->persons[$child_id];
              $this_child->add_sibling_id($prev_child_id);
              $prev_child->add_sibling_id($child_id);
        	    $this->persons[$child_id] = $this_child;
            }
          }
        	$this->persons[$prev_child_id] = $prev_child;
        }
        }

        $husband->add_child_ids($child_ids);
        $this->persons[$husband_id] = $husband;
        if ($engagement != NULL)
          $engagement->set_person_id($husband_id);
        if ($marriage != NULL)
          $marriage->set_person_id($husband_id);
        if ($divorce != NULL)
          $divorce->set_person_id($husband_id);
        if ($separation != NULL)
          $separation->set_person_id($husband_id);
      }

      if ($wife != null)
      {
        $prev_children = $wife->get_child_ids();
		if ($prev_children != null)
		{
         foreach ($prev_children as $prev_child_id => $v)
        {
        	reset($child_ids);
          $prev_child = $this->persons[$prev_child_id];
         foreach ($child_ids as $child_id => $v)
          {
            if ($child_id != $prev_child_id)
            {
              $this_child = $this->persons[$child_id];
              $this_child->add_sibling_id($prev_child_id);
              $prev_child->add_sibling_id($child_id);
        	    $this->persons[$child_id] = $this_child;
            }
          }
        	$this->persons[$prev_child_id] = $prev_child;
        }
        }

        $wife->add_child_ids($child_ids);
        $this->persons[$wife_id] = $wife;
        if ($engagement != null)
        {
          $enga2 = $engagement->get_clone();
          $negative_id = "N" . $enga2->get_id();
          $enga2->set_id($negative_id);
          $enga2->set_person_id($wife_id);
          $this->events[$negative_id] = $enga2;
        }
        if ($marriage != null)
        {
          $marr2 = $marriage->get_clone();
          $negative_id = "N" . $marr2->get_id();
          $marr2->set_id($negative_id);
          $marr2->set_person_id($wife_id);
          $this->events[$negative_id] = $marr2;
        }
        if ($divorce != null)
        {
          $div2 = $divorce->get_clone();
          $negative_id = "N" . $div2->get_id();
          $div2->set_id($negative_id);
          $div2->set_person_id($wife_id);
          $this->events[$negative_id] = $div2;
        }
        if ($separation != null)
        {
          $sep2 = $separation->get_clone();
          $negative_id = "N" . $sep2->get_id();
          $sep2->set_id($negative_id);
          $sep2->set_person_id($wife_id);
          $this->events[$negative_id] = $sep2;
        }
      }
      if ($engagement != NULL)
        $this->events[$engagement->get_id()] = $engagement;
      if ($marriage != NULL)
        $this->events[$marriage->get_id()] = $marriage;
      if ($separation != NULL)  
        $this->events[$separation->get_id()] = $separation;
      if ($divorce != NULL)
        $this->events[$divorce->get_id()] = $divorce;

      reset($children);
      if ($children)
      {
         foreach ($children as $child_id_outer => $v)

      {
        reset($child_ids);
         foreach ($children as $child_id_inner => $v)
        {
          if ($child_id_outer != $child_id_inner)
          {
            $outer_child = $this->get_person($child_id_outer);
            $outer_child->add_sibling_id($child_id_inner);
            $this->persons[$outer_child->get_id()] = $outer_child;
          }
        }
      }
      }
    }
  }

  function get_descendant_table($person_id)                          
  {
    $table = "<table cellpadding='0' cellspacing='0' border='0'><tr><th align='left'>Etterkommere (" . (MAX_DESC_LEVELS + 1) ." niv&aring;er, '+' = finnes flere)</th></tr>";
    if ($person_id == NULL)
       return $children;
    $person = $this->persons[$person_id];

    $line_levels = array();
    $level = 0;
    $line_levels[$level] = FALSE;
    $table = $this->get_descendants($table, $person, 0, $line_levels);
    
    $table = $table . "</table>";
    return $table;
  }

  function get_descendants($table, $person, $level, $line_levels)
  {
  	if ($level > MAX_DESC_LEVELS)
  	  return $table;
  	$next_level = $level + 1;

    if (!$person)
       $person = $this->get_person(1);
  	$child_ids = $person->get_child_ids();
  	if (!$child_ids || count($child_ids) == 0)
  	  return $table;

    $c = 0;
    $child_count = count($child_ids);
	foreach ($child_ids as $child_id => $v)
    {
      $child = $this->persons[$child_id];
    	if ($person->has_children())
    	  $gif_count = $level;
    	else
    	  $gif_count = $level + 1;

      $table = $table . "<tr><td nowrap>";

      for ($i = 1; $i < $gif_count; $i++)
      {
        $prev_i = $i - 1;
      	if (array_key_exists($i, $line_levels) && $line_levels[$i])
          $table = $table . "<img src=images/line.gif align=absbottom>";
        else
          $table = $table . "<img src=images/empty.gif align=absbottom>";
      }
      if ($level > 0)
      {
      	if ($c < $child_count - 1)
      	{
      		$line_levels[$level] = TRUE;
          $table = $table . "<img src=images/joinbottom.gif align=absbottom>";
        }
        else
      	{
      		$line_levels[$level] = FALSE;
          $table = $table . "<img src=images/join.gif align=absbottom>";
       }
      }

      $table = $table . format_person_short($this, $child_id, "slekt_" . $this->projectid . ".php");
      if ($level == MAX_DESC_LEVELS && $child->has_children())
        $table = $table . " <b>+</b>";
      $table = $table . "</td></tr>";
      $table = $this->get_descendants($table, $child, $next_level, $line_levels);
      $c++;
    }
    return $table;
  }

  function get_ancestors($person_id)
  {
    $ancestors = array();
    if ($person_id == NULL)
       return $ancestors;
    $person = $this->persons[$person_id];

    $ancestors = $this->get_parents($ancestors, $person, "", 0);
    return $ancestors;
  }

  function get_parents($ancestors, $person, $prefix, $level)
  {
  	if ($level > 2)
  	  return $ancestors;
  	$level++;

  	$father_id = $person->get_father_id();
  	if ($father_id != NULL)
  	{
     	$father = $this->persons[$father_id];
  	$new_prefix = $prefix . "F";
      $ancestors[$new_prefix] = $father;
      $ancestors = $this->get_parents($ancestors, $father, $new_prefix, $level);
  	}
  	$mother_id = $person->get_mother_id();
  	if ($mother_id != NULL)
  	{
     	$mother = $this->persons[$mother_id];
  	$new_prefix = $prefix . "M";
      $ancestors[$new_prefix] = $mother;
      $ancestors = $this->get_parents($ancestors, $mother, $new_prefix, $level);
  	}

  	return $ancestors;
  }

  function get_events()
  {
  	return $this->events;
  }

  function get_person_events($person_id)
  {
  	reset($this->events);
  	$person_events = array();
  	foreach ($this->events as $event_id => $event)
 	{
  		if ($event->get_person_id() == $person_id)
  			$person_events[$event_id] = $event;
  	}

  	return $person_events;
  }

  function get_event($event_id)
  {
  	return $this->events[$event_id];
  }

  function get_place($place_id)
  {
  	return $this->places[$place_id];
  }
}
?>
