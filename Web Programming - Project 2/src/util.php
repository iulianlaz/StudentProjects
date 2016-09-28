<?php
require_once 'idiorm.php';
ORM::configure('sqlite:./db.sqlite');
ORM::configure('id_column_overrides', array(
    'pw_user' => 'usr_id',
    'pw_article' => 'art_id'
));

class Util {
	/**
	 * Coduri returnate
	 */
	const STATUS_OK = 'ok';
	const STATUS_USR = 'username';
	const STATUS_PASS = 'password';
	const STATUS_PASS_STRENGTH = 'password_strength';
	const STATUS_CONFIRM = 'confirm';
	const STATUS_USR_EXISTS = 'user_exists';
	const STATUS_USR_DOESNT_EXIST = 'user_doesnt_exist';
	const STATUS_WRONG_PASS = 'wrong_password';
	const STATUS_WRONG_CAT = 'wrong_cat';
	const STATUS_WRONG_ART = 'wrong_art';	
	const STATUS_WRONG_TABLE = 'wrong_table';
	
	const STATUS_ID = 'id';
	const STATUS_TITLE = 'title';
	const STATUS_CONTENT = 'content';
	const STATUS_AUTHOR = 'author';
	const STATUS_CAT_ID = 'cat_id';
	const STATUS_S = 's';
	
	/**
	 * Etichete folosite pentru verificare existentei unui user in baza de date
	 */
	const REGISTER = 'register';
	const LOGIN = 'login';
	
	/**
	 * Caractere folosite pentr generare salt
	 */
	const CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	/**
	 * Functie pentru generare salt
	 */
	public static function generateRandString($length) {
		srand(time());
		$str = '';
		$size = strlen(self::CHARS);
		$strChars = self::CHARS;
		for($i = 0; $i < $length; $i++ ) {
			$str .= $strChars[rand(0, $size - 1)];
		}
		return $str;
	}

	/**
	 * Validare username
	 */
	public static function checkUsername($username) {
		if ((empty($username)) || (strlen($username) < 6)) {
			return self::STATUS_USR;
		}
		return self::STATUS_OK;	
	}

	/**
	 * Validare parola
	 */
	public static function checkPassword($password) {
		if ((empty($password)) || (strlen($password) < 6)) {
			return self::STATUS_PASS;
		}
		return self::STATUS_OK;
	}

	/**
	 * Verificare siguranta parolei
	 */
	public static function checkPasswordStrength($pwd) {
		//$errors_init = $errors;
 
    		if (strlen($pwd) < 6) {
        		//$errors[] = "Password too short!";
			return self::STATUS_PASS_STRENGTH;
    		}
 
    		if (!preg_match("#[0-9]+#", $pwd)) {
        		//$errors[] = "Password must include at least one number!";
			return self::STATUS_PASS_STRENGTH;
    		}
 
    		if (!preg_match("#[a-zA-Z]+#", $pwd)) {
        		//$errors[] = "Password must include at least one letter!";
			return self::STATUS_PASS_STRENGTH;		
    		}     
 
    		//return ($errors == $errors_init);
		return self::STATUS_OK;
	}

	/**
	 * Verificare confirmare parola
	 */
	public static function checkConfirm($confirm, $password) {
		if ((strcmp($confirm, $password) != 0)) {
			return self::STATUS_CONFIRM;
		}
		return self::STATUS_OK;	
	}

	/**
	 * Verificare daca userul exista in baza de date
	 */
	public static function checkExists($username, $label) {
		$user = ORM::for_table('pw_user')->where('usr_username', $username)->find_one();
		if (!empty($user) && (strcmp($label, self::REGISTER) == 0)) {
			return Util::STATUS_USR_EXISTS;
		} else {
			if (empty($user) && (strcmp($label, self::LOGIN) == 0)) {
				return Util::STATUS_USR_DOESNT_EXIST;
			}
		}

		return self::STATUS_OK;
	}

	/**
	 * Verificare daca parola introdusa corespunde cu cea din baza de date
	 */
	public static function checkCorrectPassword($username, $password) {
		$user = ORM::for_table('pw_user')->select('usr_salt')->where('usr_username' , $username)->find_one();
		$result = ORM::for_table('pw_user')->where_raw('((`usr_username` = ?) AND (`usr_password` = ?))', array ($username, sha1($password . $user->usr_salt)))->find_one();
		if (empty($result)) {
			return self::STATUS_WRONG_PASS;
		}
		return self::STATUS_OK;
	}

}


