<?php

class RootItem
{
    public $id = 0;
    public $name = "Ikke satt";

    public function __construct($id, $name)
    {
        $this->id = $id;
        $this->name = $name;
    }

    function get_id()
    {
        return $this->id;
    }

    function set_id($id)
    {
        $this->id = $id;
    }

    public function get_name()
    {
        return $this->name;
    }

    function set_name($name)
    {
        $this->name = $name;
    }
}

class Person extends RootItem
{
    var $firstname;
    var $lastname;
    var $gender;
    var $histregid;
    var $ancestry_category;
    var $birth;
    var $death;
    var $father_id;
    var $mother_id;
    var $child_ids;
    var $sibling_ids;

    public function __construct($id, $name)
    {
        parent::__construct($id, $name);

        $pos = strpos($name, "/");
        $firstname = substr($name, 0, $pos);
        $firstname = str_replace("XX","<u>",$firstname);
        $firstname = str_replace("YY","</u>",$firstname);

        $lastname = substr($name, $pos + 1, strlen($name) - ($pos + 2));

        $this->firstname = $firstname;
        $this->lastname = $lastname;

        $this->set_name(trim($this->firstname) . " " . trim($this->lastname));
        
        $this->birth = new Event(-1, NULL);
        $this->death = new Event(-1, NULL);
    }

    function set_histregid($histregid)
    {
    	$this->histregid = $histregid;
    }

    function get_histregid()
    {
    	return $this->histregid;
    }

    function set_gender($gender)
    {
    	$this->gender = $gender;
    }

    function get_gender()
    {
    	return $this->gender;
    }

    function set_ancestry_category($ancestry_category)
    {
    	$this->ancestry_category = $ancestry_category;
    }

    function get_ancestry_category()
    {
    	return $this->ancestry_category;
    }

    function set_birth($birth)
    {
    	$this->birth = $birth;
    	
    	$birth_date = $this->birth->get_date();
    	if (!$birth_date)
    		return;

        $caret_pos = strlen($birth_date) - 4;

        $year = substr($birth_date, $caret_pos, 4);
        $age = THIS_YEAR - intval($year);

        if ($age > 87 && $age != THIS_YEAR)
        {
            $death = new Event($this->birth->get_id() * -1, GED_DEATH);
            $death->set_date("?");
            $this->set_death($death);
        }
    }

    function get_birth()
    {
    	return $this->birth;
    }

    function set_death($death)
    {
    	$this->death = $death;
//echo $this->name . $this->death->get_date() . "<br>";
    }

    function get_death()
    {
    	return $this->death;
    }

    function set_father_id($father_id)
    {
    	$this->father_id = $father_id;
    }

    function get_father_id()
    {
    	return $this->father_id;
    }

    function set_mother_id($mother_id)
    {
    	$this->mother_id = $mother_id;
    }

    function get_mother_id()
    {
    	return $this->mother_id;
    }

    function add_child_id($child_id)
    {
        $this->child_ids[$child_id] = $child_id;
    }

    function add_child_ids($child_ids)
    {
  		foreach ($child_ids as $child_id => $v)
            $this->child_ids[$child_id] = $child_id;
    }

    function get_child_ids()
    {
    	return $this->child_ids;
    }

    function add_sibling_id($sibling_id)
    {
        $this->sibling_ids[$sibling_id] = $sibling_id;
    }

    function get_sibling_ids()
    {
    	return $this->sibling_ids;
    }

    function has_children()
    {
        if ($this->child_ids)
    		return count($this->child_ids) > 0;
    	else
    		return false;
    }
}

class Family extends RootItem
{
    var $marriage_id;
    var $engagement_id;
    var $divorce_id;
    var $separation_id;
    var $wife_id;
    var $husband_id;
    var $child_ids = array();
    var $sibling_ids = array();
    

    public function __construct($id, $name)
    {
        parent::__construct($id, NULL);
    }

    function set_marriage_id($marriage_id)
    {
    	$this->marriage_id = $marriage_id;
    }

    function get_marriage_id()
    {
    	return $this->marriage_id;
    }

    function set_engagement_id($engagement_id)
    {
    	$this->engagement_id = $engagement_id;
    }

    function get_engagement_id()
    {
    	return $this->engagement_id;
    }

    function set_separation_id($separation_id)
    {
    	$this->separation_id = $separation_id;
    }

    function get_separation_id()
    {
    	return $this->separation_id;
    }

    function set_divorce_id($divorce_id)
    {
    	$this->divorce_id = $divorce_id;
    }

    function get_divorce_id()
    {
    	return $this->divorce_id;
    }

    function set_husband_id($husband_id)
    {
    	$this->husband_id = $husband_id;
    }

    function get_husband_id()
    {
    	return $this->husband_id;
    }

    function set_wife_id($wife_id)
    {
    	$this->wife_id = $wife_id;
    }

    function get_wife_id()
    {
    	return $this->wife_id;
    }

    function add_child_id($child_id)
    {
        $this->child_ids[$child_id] = $child_id;
    }

    function add_child_ids($child_ids)
    {
  		foreach ($child_ids as $child_id => $v)
            $this->child_ids[$child_id] = $child_id;
    }

    function get_child_ids()
    {
    	return $this->child_ids;
    }
}

class Source extends RootItem
{
    public function __construct($id, $name)
    {
        parent::__construct($id, $name);
    }
}

class Place extends RootItem
{
    public function __construct($id, $name)
    {
        parent::__construct($id, $name);
    }
}

class Event extends RootItem
{
    var $type;
    var $person_id;
    var $date;
    var $place;
    var $source;
    var $sourceref;

    public function __construct($id, $type)
    {
        parent::__construct($id, $type);
        $this->type = $type;
    }

    function set_person_id($person_id)
    {
    	$this->person_id = $person_id;
    }

    function get_person_id()
    {
    	return $this->person_id;
    }

    function set_date($date)
    {
    	$this->date = $date;
    }

    function get_date()
    {
    	return $this->date;
    }

    function get_type()
    {
    	return $this->type;
    }
    
    function get_clone()
    {
    	$event = new Event($this->id, $this->type);
    	$event->set_date($this->date);
    	$event->set_place($this->place);
    	$event->set_source($this->source);
    	$event->set_sourceref($this->sourceref);

    	return $event;
    }

    function set_place($place)
    {
    	$this->place = $place;
    }

    function get_place()
    {
    	return $this->place;
    }

    function set_source($source)
    {
    	$this->source = $source;
    }

    function get_source()
    {
    	return $this->source; 
    }

    function set_sourceref($sourceref)
    {
    	$this->sourceref = $sourceref;
    }

    function get_sourceref()
    {
    	return $this->sourceref;
    }

    function add_note($note)
    {
    }

    function update_last_note($note)
    {
    }
}

class ListItem extends RootItem
{
	var $type;

    public function __construct($id, $name)
    {
        parent::__construct($id, $name);
    }

    function set_type($type)
    {
    	$this->type = $type;
    }

    function get_type()
    {
    	return $this->type;
    }
}
?>
