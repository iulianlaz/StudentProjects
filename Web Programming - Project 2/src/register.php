<?php
require_once('util.php');

class Register {
	/**
	 * Username, parola si confirmarea parolei
	 */
	private $_username;
	private $_password;
	private $_confirm;	

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

		$this->_confirm = mysql_real_escape_string($_POST['confirm']);
		
		$this->status = $this->checkInformation();
		if (strcmp($this->status, Util::STATUS_OK) == 0) {
        		$this->saveInformation();
		}
	}

	/** 
	 * Verficam informatiile primite
	 */
	public function checkInformation() {
		
		$result = Util::checkPasswordStrength($this->_password);
		if (strcmp($result, Util::STATUS_OK) != 0) {
			return $result;
		}

		$result = Util::checkConfirm($this->_confirm, $this->_password);
		if (strcmp($result, Util::STATUS_OK) != 0) {
			return $result;
		}

		$result = Util::checkExists($this->_username, Util::REGISTER);
		if (strcmp($result, Util::STATUS_OK) != 0) {
			return $result;
		}

		return Util::STATUS_OK;
	}

	/**
	 * Salvam informatiile in baza de date
	 */
	public function saveInformation() {
		$user = ORM::for_table('pw_user')->create();

		$user->usr_username = $this->_username;
		$usrSalt = Util::generateRandString(30);
		$user->usr_password = sha1($this->_password . $usrSalt);
		$user->usr_salt = $usrSalt;
		$user->set_expr('usr_register_date', 'DATETIME("now")');
		$user->usr_last_login = "0000-00-00 00:00:00";
		$user->save();
	}
}

$register = new Register();
echo $register->status;
