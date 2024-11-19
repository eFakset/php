<?php
class PersonImages {
	var $person_images = array();
	public function __construct() {
		$this->person_images[1] = array("Foto\P28_I1.jpg", "74", "100");
		$this->person_images[2] = array("Foto\P28_I2.jpg", "71", "100");
		$this->person_images[3] = array("Foto\P28_I3.jpg", "76", "100");
		$this->person_images[4] = array("Foto\P28_I4.jpg", "72", "100");
		$this->person_images[5] = array("Foto\P28_I5.jpg", "72", "100");
		$this->person_images[6] = array("Foto\P28_I6.jpg", "74", "100");
		$this->person_images[7] = array("Foto\P28_I7.jpg", "77", "100");
		$this->person_images[9] = array("Foto\P28_I9.jpg", "79", "100");
		$this->person_images[11] = array("Foto\P28_I11.jpg", "71", "100");
		$this->person_images[12] = array("Foto\P28_I12.jpg", "85", "100");
		$this->person_images[15] = array("Foto\P28_I15.jpg", "51", "100");
}
	function get_person_image($id) {
		$image_info = array();
		if (array_key_exists($id, $this->person_images))
			$image_info = $this->person_images[$id];
		return $image_info;
	}
}
?>
