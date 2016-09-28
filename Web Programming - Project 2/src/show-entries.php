<?php
require_once('util.php');

class ShowEntries {
	private $_table;

	public $status;

	public function __construct() {
		if (!isset($_GET['table'])) {
			$this->status = Util::STATUS_WRONG_TABLE;
			return;
		}
		$this->_table = $_GET['table'];
		$this->status = $this->checkInformation();
		if (strcmp($this->status, Util::STATUS_OK) == 0) {
			$this->status = $this->getTables();
		}
	}

	public function checkInformation() {
		$result = preg_match('/^[A-Za-z0-9_]+$/', $this->_table);
		if ($result === 0) {
			return Util::STATUS_WRONG_TABLE;
		}

		$tables = ORM::for_table('sqlite_master')->find_many();
		$exists = false;
		foreach($tables as $table) {
			if (strcmp($table->tbl_name, $this->_table) == 0) {
				$exists = true;
			} 
		}
		if (!$exists) {
			return Util::STATUS_WRONG_TABLE;
		}
	
		return Util::STATUS_OK;
	}

	public function getTables() {
		$rows = ORM::for_table($this->_table)->find_many();
		$result = array();
		foreach($rows as $row) {
			$data = $row->as_array();
			$result[] = $data;
		}
		return json_encode($result);	
	}
}

$table = new ShowEntries();
echo $table->status;
