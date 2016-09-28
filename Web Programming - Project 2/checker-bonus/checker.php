<?php require_once('settings.php'); ?>
<!DOCTYPE html>
<html>
<head>
	<title>Chcker Tema 2 Programare Web</title>
	<meta charset="UTF-8">
	<link href="css/bootstrap.css" rel="stylesheet" type="text/css">
	<link href="css/checker.css" rel="stylesheet" type="text/css">
	<script src="js/jquery-1.11.0.min.js"></script>
	<script src="js/sha1.js"></script>
	<script src="js/checker.js"></script>
</head>
<body>

	<h1>Checker Tema 2 cu Bonus Programare Web v0.1</h1>
	<p>Your score: <span id="total-score">Not checked yet</span></p>
	
	<button class="btn btn-primary" id="check-now" type="button">Check now</button>
	
	<?php if(isset($tasks)) foreach($tasks as $k => $task) : ?>
	<div class="task task<?=$k?>">
		<h2>Task <?=$k?> - <?=$task['name']?></h2>
		<?php if(isset($task['subtasks'])) foreach($task['subtasks'] as $ks => $subtask) : ?>
		<div class="task task<?=$k?>-<?=$ks?>">
			<span class="score"><?=$subtask['score']?></span>
			<h3>Task <?=$k?>-<?=$ks?> - <?=$subtask['name']?></h3>
			<h4 class="description"><?=$subtask['description']?></h4>
			<div class="passed alert alert-success">Passed <b>+<?=$subtask['score']?></b></div>
			<div class="failed alert alert-error">Failed <b>-<?=$subtask['score']?></div>
		</div>
		<?php endforeach; ?>
	</div>
	<?php endforeach;?>
	
</body>
</html>