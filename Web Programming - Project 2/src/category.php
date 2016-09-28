<?php
require_once('util.php');

class Category {
	/**
	 * Id-ul categoriei
	 */
	private $_category;	
	
	/**
	 * Rezultatul intors
	 */
	public $status;

	public function __construct() {
		if (!isset($_GET['cat_id'])) {
			$this->status = Util::STATUS_WRONG_CAT;
			return;
		}
		$this->_category = mysql_real_escape_string($_GET['cat_id']);
		
		$this->status = $this->checkCategory();
		if (strcmp($this->status, Util::STATUS_OK) == 0) {
			$this->status = $this->getArticles();
		}
	}

	/**
	 * Se verifica daca acesta categorie este intreg si daca exista in baza de date
	 */
	public function checkCategory() {
		if (!is_numeric($this->_category)) {
			return Util::STATUS_WRONG_CAT;
		}
		$categ = ORM::for_table('pw_category')->where('cat_id', $this->_category)->find_one();
		if (empty($categ)) {
			return Util::STATUS_WRONG_CAT;
		}
		return Util::STATUS_OK;		
	}
	
	public static function cmp($a, $b) {
		return strcmp($b->id, $a->id);
	}

	/**
	 * Returnam articolele corespunzatoare categoriei
	 */
	public function getArticles() {
		//$artIds = ORM::for_table('pw_article_category')->where('artc_cat_id', $this->_category)->find_many();
		$articles = ORM::for_table('pw_article_category')->
				select('art_id', 'id')->
				select('art_title', 'title')->
				select('art_content', 'content')->
				select('art_views', 'views')->
				select('usr_username', 'author')->
				select('art_publish_date', 'publish_date')->
				select('art_update_date', 'update_date')->
				join('pw_article', array ('pw_article.art_id', '=', 'pw_article_category.artc_art_id'))->
				join('pw_category', array ('pw_category.cat_id', '=', 'pw_article_category.artc_cat_id'))->
				join('pw_user', array('pw_user.usr_id', '=', 'pw_article.art_author'))->where('pw_category.cat_id', $this->_category)->order_by_desc('publish_date')->find_many();
		
		$result = array();
		foreach($articles as $article) {
			$data = $article->as_array();
			$result[] = $data;
		}
		return json_encode($result);
	}
}

$categ = new Category();
echo $categ->status;
