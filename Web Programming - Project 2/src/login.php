<?php
require_once('util.php');

class Login {
	/**
	 * Username si parola
	 */
	private $_username;
	private $_password;

	/**
	 * Rezultatul intors
	 */
	public $status;

	public function __construct() {
		
		if (!isset($_POST['username'])) { 
			$this->status =  Util::STATUS_USR;
			return;
		}
		$this->_username = mysql_real_escape_string($_POST['username']);
		$result = Util::checkUsername($this->_username);
		if (strcmp($result, Util::STATUS_OK) != 0) {
			$this->status =  $result;
			return;
		}
		
		if (!isset($_POST['password'])) {
			$this->status =  Util::STATUS_PASS;
			return;
		}
		$this->_password = mysql_real_escape_string($_POST['password']);
		$result = Util::checkPassword($this->_password);	
		if (strcmp($result, Util::STATUS_OK) != 0) {
			$this->status =  $result;
			return;
		}

		$this->status = $this->checkInformation();
		if (strcmp($this->status, Util::STATUS_OK) == 0) {
			$this->updateLastLogin($this->_username);
		}		
	}

	/**
	 * Verificam credentialele primite
	 */
	public function checkInformation() {

		$result = Util::checkExists($this->_username, Util::LOGIN);
		if (strcmp($result, Util::STATUS_OK) != 0) {
			return $result;
		}

		$result = Util::checkCorrectPassword($this->_username, $this->_password);
		if (strcmp($result, Util::STATUS_OK) != 0) {
			return $result;
		}
		
		return Util::STATUS_OK;
	}

	/**
	 * Se actualizeaza valoarea campului usr_last_login
	 */
	public function updateLastLogin($username) {
		$user = ORM::for_table('pw_user')->where('usr_username', $username)->find_one();
		$user->set_expr('usr_last_login', 'DATETIME("NOW")');
		$user->save();
	}
}

$login = new Login();
echo $login->status;
