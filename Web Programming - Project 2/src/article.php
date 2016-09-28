<?php
require_once('util.php');

class Article {
	private $_artId;
	
	public $status;	

	public function __construct() {
		if (!isset($_GET['art_id'])) {
			$this->status = Util::STATUS_WRONG_ART;
			return;
		}
		$this->_artId = $_GET['art_id'];
		$this->status = $this->checkInformation();
		if (strcmp($this->status, Util::STATUS_OK) == 0) {
			$this->status = $this->getArticle();
		}
	}

	public function checkInformation() {
		if (!is_numeric($this->_artId)) {
			return Util::STATUS_WRONG_ART;
		}

		$art = ORM::for_table('pw_article')->where('art_id', $this->_artId)->find_one();
		if (empty($art)) {
			return Util::STATUS_WRONG_ART;
		}

		return Util::STATUS_OK;
	}

	public function getArticle() {
		$article = ORM::for_table('pw_article')->
				select('art_id', 'id')->
				select('art_title', 'title')->
				select('art_content', 'content')->
				select('art_views', 'views')->
				select('usr_username', 'author')->
				select('art_publish_date', 'publish_date')->
				select('art_update_date', 'update_date')->
				join('pw_user', array ('pw_article.art_author', '=', 'pw_user.usr_id'))->where('pw_article.art_id', $this->_artId)->find_one();
		
		$data = $article->as_array();	

		// Update views
		$update = ORM::for_table('pw_article')->where('pw_article.art_id', $this->_artId)->find_one();
		$update->art_views = $update->art_views + 1;
		$update->save();
		
		
		return json_encode($data);
	}
}

$article = new Article();
echo $article->status;
