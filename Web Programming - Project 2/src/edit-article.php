<?php
require_once('util.php');

class EditArticle {
	/**
	 * Campurile articolului
	 */
	private $_id;
	private $_title;
	private $_content;
	private $_author;
	private $_catId;
	
	/**
	 * Rezultatul intors
	 */
	public $status;

	public function __construct() {
		if ((!isset($_POST['id'])) || (!is_numeric($_POST['id']))) {
			$this->status = Util::STATUS_ID;
			return;
		}
		$this->_id = $_POST['id'];
		$this->status = $this->checkInformation();	
		if (strcmp($this->status, Util::STATUS_OK) == 0) {
			$this->updateArticle();
		}
	}

	/**
	 * Verificare informatii primite
	 */
	public function checkInformation() {
		$result = $this->checkTitle();
		if (strcmp(Util::STATUS_OK, $result) != 0) {
			return $result;

		}
		$result = $this->checkContent();
		if (strcmp(Util::STATUS_OK, $result) != 0) {
			return $result;
		}

		$result = $this->checkAuthor();
		if (strcmp(Util::STATUS_OK, $result) != 0) {
			return $result;
		}

		$result = $this->checkCatId();
		if (strcmp(Util::STATUS_OK, $result) != 0) {
			return $result;
		}

		return Util::STATUS_OK;
	}

	public function checkTitle() {
		if ((!isset($_POST['title'])) || (empty($_POST['title']))) {
			return Util::STATUS_TITLE;
		}
		$this->_title = $_POST['title'];
		return Util::STATUS_OK;
	}

	public function checkContent() {
		if ((!isset($_POST['content'])) || (empty($_POST['content']))) {
			return Util::STATUS_CONTENT;
		}
		$this->_title = $_POST['content'];
		return Util::STATUS_OK;
	}

	public function checkAuthor() {
		if ((!isset($_POST['author'])) || (empty($_POST['author']))) {
			return Util::STATUS_AUTHOR;
		}
		$this->_author = $_POST['author'];
		$user = ORM::for_table('pw_user')->where('usr_id', $this->_author)->find_one();
		
		if (empty($user)) {
			return Util::STATUS_AUTHOR;
		}		
		return Util::STATUS_OK;
	}

	public function checkCatId() {
		if ((!isset($_POST['cat_id'])) || (empty($_POST['cat_id']))) {
			return Util::STATUS_CAT_ID;
		}
		$this->_catId = $_POST['cat_id'];
		$catIds = $this->_catId;
		foreach($catIds as $catId) {
			$cat = ORM::for_table('pw_category')->where('cat_id', $catId)->find_one();
			if(empty($cat)) {
				return Util::STATUS_CAT_ID;
			}
		}
		return Util::STATUS_OK;
	}

	public function updateArticle() {
		$article = ORM::for_table('pw_article')->where('art_id', $this->_id)->find_one();

		$article->art_title = $this->_title;
		$article->art_content = $this->_content;
		$article->art_author = $this->_author;
		$article->set_expr('art_update_date', 'DATETIME("NOW")');
		$article->save();

		foreach($this->_catId as $catId) {
			$artCateg = ORM::for_table('pw_article_category')->create();
			$artCateg->artc_art_id = $this->_id;
			$artCateg->artc_cat_id = $catId;
		}
	}	
}

$edit = new EditArticle();
echo $edit->status;
	
