<?php
	define('STUDENT_ID',13); // put your student id from http://pw.dictionarit.eu/tema02-student-list.php here
	define('URL_TEMA2','http://localhost/pw-tema2/'); // put the link to your homework here
	define('URL_CHECKER','http://pw.dictionarit.eu');
	
	$tasks = array(
		1 => array(
			'name' => 'show-entries.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request show-entries.php with no <i>table</i> GET parameter',
					'description' => 'Should print wrong_table',
					'score' => 0.005,
				),
				2 => array(
					'name' => 'Request show-entries.php with <i>pw_article!</i> for <i>table</i> GET parameter',
					'description' => 'Should print wrong_table',
					'score' => 0.005,
				),
				3 => array(
					'name' => 'Request show-entries.php with <i>pw_user</i> for <i>table</i> GET parameter',
					'description' => 'Should print the same result as '.getHtmlLink(URL_CHECKER.'/show-entries.php?student='.STUDENT_ID.'&table=pw_user&bonus=true'),
					'score' => 0.01,
				),
				4 => array(
					'name' => 'Request show-entries.php with <i>pw_article</i> for <i>table</i> GET parameter',
					'description' => 'Should print the same result as '.getHtmlLink(URL_CHECKER.'/show-entries.php?student='.STUDENT_ID.'&table=pw_article&bonus=true'),
					'score' => 0.01,
				),
				5 => array(
					'name' => 'Request show-entries.php with <i>pw_category</i> for <i>table</i> GET parameter',
					'description' => 'Should print the same result as '.getHtmlLink(URL_CHECKER.'/show-entries.php?student='.STUDENT_ID.'&table=pw_category&bonus=true'),
					'score' => 0.01,
				),
				6 => array(
					'name' => 'Request show-entries.php with <i>pw_article_category</i> for <i>table</i> GET parameter',
					'description' => 'Should print the same result as '.getHtmlLink(URL_CHECKER.'/show-entries.php?student='.STUDENT_ID.'&table=pw_article_category&bonus=true'),
					'score' => 0.01,
				),
			),
		),
		2 => array(
			'name' => 'register.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request register.php with no POST parameters',
					'description' => 'Should print username',
					'score' => 0.01,
				),
				2 => array(
					'name' => 'Request register.php with <i>username</i> POST parameter having length less than 6 characters',
					'description' => 'Should print username',
					'score' => 0.01,
				),
				3 => array(
					'name' => 'Request register.php with <i>password</i> POST parameter having length less than 6 characters',
					'description' => 'Should print password',
					'score' => 0.01,
				),
				4 => array(
					'name' => 'Request register.php with <i>confirm</i> POST parameter being different from <i>password</i> POST parameter ',
					'description' => 'Should print confirm',
					'score' => 0.01,
				),
				5 => array(
					'name' => 'Request register.php with <i>username</i> POST parameter being equal to one table entry',
					'description' => 'Should print user_exists',
					'score' => 0.01,
				),
				6 => array(
					'name' => 'Request register.php with valid POST parameters',
					'description' => 'Should print ok',
					'score' => 0.05,
				),
				7 => array( // bonus
					'name' => 'Request register.php with <i>password</i> POST parameter not being strong enough',
					'description' => 'Should print password_strength',
					'score' => 0.025,
				),
				8 => array( // bonus
					'name' => 'Check that password for user created at task2-6 has been saved encrypted',
					'description' => 'Should print the encrypted password in the pw_user table fields list',
					'score' => 0.05,
				),
			),
		),
		3 => array(
			'name' => 'login.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request login.php with no POST parameters',
					'description' => 'Should print username',
					'score' => 0.01,
				),
				2 => array(
					'name' => 'Request login.php with <i>username</i> POST parameter having length less than 6 characters',
					'description' => 'Should print username',
					'score' => 0.01,
				),
				3 => array(
					'name' => 'Request login.php with <i>password</i> POST parameter having length less than 6 characters',
					'description' => 'Should print password',
					'score' => 0.01,
				),
				4 => array(
					'name' => 'Request login.php with <i>username</i> POST parameter being equal to an inexistent user',
					'description' => 'Should print user_doesnt_exist',
					'score' => 0.01,
				),
				5 => array(
					'name' => 'Request login.php with valid POST parameters',
					'description' => 'Should print ok',
					'score' => 0.01,
				),
				6 => array( // bonus
					'name' => 'Check if last_login has been updated after last request',
					'description' => 'Should print last login datetime in the pw_user table fields list',
					'score' => 0.025,
				),
			),
		),
		4 => array(
			'name' => 'article.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request article.php with no GET parameter',
					'description' => 'Should print wrong_art',
					'score' => 0.01,
				),
				2 => array(
					'name' => 'Request article.php with <i>art_id</i> GET parameter not being integer',
					'description' => 'Should print wrong_art',
					'score' => 0.01,
				),
				3 => array(
					'name' => 'Request article.php with <i>art_id</i> GET parameter having an integer value, but for an inexistent article',
					'description' => 'Should print wrong_art',
					'score' => 0.03,
				),
				4 => array(
					'name' => 'Request article.php with <i>art_id</i> GET parameter being equal to an existent article',
					'description' => 'Should print a JSON format for the article',
					'score' => 0.05,
				),
				5 => array( // bonus
					'name' => 'Check if views has been updated after last request',
					'description' => 'Should print the number of views for the article in the article.php request',
					'score' => 0.025,
				),
			),
		),
		5 => array(
			'name' => 'category.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request category.php with no GET parameter',
					'description' => 'Should print wrong_cat',
					'score' => 0.01,
				),
				2 => array(
					'name' => 'Request category.php with <i>cat_id</i> GET parameter not being integer',
					'description' => 'Should print wrong_cat',
					'score' => 0.01,
				),
				3 => array(
					'name' => 'Request category.php with <i>cat_id</i> GET parameter having an integer value, but for an inexistent category',
					'description' => 'Should print wrong_cat',
					'score' => 0.03,
				),
				4 => array(
					'name' => 'Request category.php with <i>cat_id</i> GET parameter being equal to an existent category',
					'description' => 'Should print a JSON format for the articles in the category',
					'score' => 0.05,
				),
			),
		),
		6 => array(
			'name' => 'search.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request search.php with no GET parameter',
					'description' => 'Should print s',
					'score' => 0.01,
				),
				2 => array(
					'name' => 'Request search.php with <i>s</i> GET parameter being empty',
					'description' => 'Should print s',
					'score' => 0.01,
				),
				3 => array(
					'name' => 'Request search.php with <i>s</i> GET parameter being set correctly as first two letters from an article title',
					'description' => 'Should print a JSON format for the articles having that word in the title or in the content',
					'score' => 0.03,
				),
				4 => array(
					'name' => 'Request search.php with <i>s</i> GET parameter being set correctly as first word from an article content',
					'description' => 'Should print a JSON format for the articles having that word in the title or in the content',
					'score' => 0.05,
				),
				5 => array( // bonus
					'name' => 'Request search.php with <i>s</i> GET parameter being set correctly as first two letters from an article title and 
						<cat_id> GET parameter being set correctly as the category for that article',
					'description' => 'Should print a JSON format for the articles having that word in the title or in the content and being in 
						that category',
					'score' => 0.05,
				),
			),
		),
		7 => array(
			'name' => 'edit-article.php',
			'subtasks' => array(
				1 => array(
					'name' => 'Request edit-article.php with no POST parameters',
					'description' => 'Should print id',
					'score' => 0.005,
				),
				2 => array(
					'name' => 'Request edit-article.php with <i>id</i> POST parameter not being integer',
					'description' => 'Should print id',
					'score' => 0.005,
				),
				3 => array(
					'name' => 'Request edit-article.php with <i>title</i> POST parameter not being set',
					'description' => 'Should print title',
					'score' => 0.005,
				),
				4 => array(
					'name' => 'Request edit-article.php with <i>content</i> POST parameter not being set',
					'description' => 'Should print content',
					'score' => 0.005,
				),
				5 => array(
					'name' => 'Request edit-article.php with <i>author</i> POST parameter not being set',
					'description' => 'Should print author',
					'score' => 0.005,
				),
				6 => array(
					'name' => 'Request edit-article.php with <i>cat_id</i> POST parameter not being set',
					'description' => 'Should print cat_id',
					'score' => 0.005,
				),
				7 => array(
					'name' => 'Request edit-article.php with <i>cat_id</i> POST parameter trying to change article categories',
					'description' => 'Should print ok and be listed in the categories page',
					'score' => 0.03,
				),
				8 => array(
					'name' => 'Request edit-article.php with <i>author</i> POST parameter trying to change article author',
					'description' => 'Should print ok and the information should be visible in the article page',
					'score' => 0.02,
				),
				9 => array(
					'name' => 'Request edit-article.php with <i>title</i> POST parameter trying to change article title',
					'description' => 'Should print ok and be listed in the search page with that term',
					'score' => 0.02,
				),
				10 => array( // bonus
					'name' => 'Check if update date has been updated after last article changes',
					'description' => 'Should print update datetime in the article page',
					'score' => 0.025,
				),
			),
		),
	);
	
	
	function getHtmlLink($link) {
		return '<a href="'.$link.'" target="_blank">'.$link.'</a>';
	}