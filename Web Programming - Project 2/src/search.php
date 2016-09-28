<?php
require_once('util.php');

class Search {

	public $status;

	public function __construct() {
		if ((!isset($_GET['s'])) || (empty($_GET['s']))) {
			$this->status = Util::STATUS_S;
			return;
		}

		$this->status = $this->getArticle($_GET['s']);	
	}

	

	public function getArticle($str) {
		$string = '%' . $str . '%';
		$article = ORM::for_table('pw_article')->
				select('art_id', 'id')->
				select('art_title', 'title')->
				select('art_content', 'content')->
				select('art_views', 'views')->
				select('usr_username', 'author')->
				select('art_publish_date', 'publish_date')->
				select('art_update_date', 'update_date')->
				join('pw_user', array ('pw_article.art_author', '=', 'pw_user.usr_id'))->where_raw('(`title` LIKE ? OR `content` LIKE ?)', array($string, $string))->order_by_desc('publish_date')->find_many();
		
		$result = array();
		foreach($article as $dataOne) {
			$res = $dataOne->as_array();
			$result[] = $res;
		}

		return json_encode($result);
	}

}

$search = new Search();
echo $search->status;
