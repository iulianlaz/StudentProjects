var STUDENT_ID = 13; // put your student id from http://pw.dictionarit.eu/tema02-student-list.php here
var URL_TEMA2 = "http://localhost/pw-tema2/"; // put the link to your homework here
var URL_CHECKER = "http://pw.dictionarit.eu";
var checker;
jQuery(document).ready(function($) {
	checker = function() {
		var score = 0;
		
		var tasks = function() {
			$(".task1").fadeIn();
			
			$.ajaxSetup({async:false});
			$.get( URL_TEMA2+"/show-entries.php", { } ).done(function( data ) {
				if (data.localeCompare("wrong_table") == 0) {
					updateScore($(".task1 .task1-1 .score").text(), "task1-1");
					$(".task1 .task1-1 .passed").show();
				}
				else $(".task1 .task1-1 .failed").show();
				printScore();
				$(".task1-1").fadeIn();
			}).error(function( data ) {
				$(".task1 .task1-1 .failed").show();
				printScore();
				$(".task1-1").fadeIn();
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_article!" } ).done(function( data ) {
				if (data.localeCompare("wrong_table") == 0) {
					updateScore($(".task1 .task1-2 .score").text(), "task1-2");
					$(".task1 .task1-2 .passed").show();
				}
				else $(".task1 .task1-2 .failed").show();
				printScore();
				$(".task1-2").fadeIn();
			}).error(function( data ) {
				$(".task1 .task1-2 .failed").show();
				printScore();
				$(".task1-2").fadeIn();
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_user" } ).done(function( data ) {
				data = $.parseJSON(data);
				$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_user", bonus: true } ).done(function( data2 ) {
					data2 = $.parseJSON(data2);
					if (JSON.stringify(data) === JSON.stringify(data2) ) {
						updateScore($(".task1 .task1-3 .score").text(), "task1-3");
						$(".task1 .task1-3 .passed").show();
					}
					else $(".task1 .task1-3 .failed").show();
					printScore();
					$(".task1-3").fadeIn();
				});
			}).error(function( data ) {
				$(".task1 .task1-3 .failed").show();
				printScore();
				$(".task1-3").fadeIn();
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_article" } ).done(function( data ) {
				data = $.parseJSON(data);
				$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_article", bonus: true } ).done(function( data2 ) {
					data2 = $.parseJSON(data2);
					if (JSON.stringify(data) === JSON.stringify(data2) ) {
						updateScore($(".task1 .task1-4 .score").text(), "task1-4");
						$(".task1 .task1-4 .passed").show();
					}
					else $(".task1 .task1-4 .failed").show();
					printScore();
					$(".task1-4").fadeIn();
				});
			}).error(function( data ) {
				$(".task1 .task1-4 .failed").show();
				printScore();
				$(".task1-4").fadeIn();
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_category" } ).done(function( data ) {
				data = $.parseJSON(data);
				$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_category", bonus: true } ).done(function( data2 ) {
					data2 = $.parseJSON(data2);
					if (JSON.stringify(data) === JSON.stringify(data2) ) {
						updateScore($(".task1 .task1-5 .score").text(), "task1-5");
						$(".task1 .task1-5 .passed").show();
					}
					else $(".task1 .task1-5 .failed").show();
					printScore();
					$(".task1-5").fadeIn();
				});
			}).error(function( data ) {
				$(".task1 .task1-5 .failed").show();
				printScore();
				$(".task1-5").fadeIn();
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_article_category" } ).done(function( data ) {
				data = $.parseJSON(data);
				$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_article_category", bonus: true } ).done(function( data2 ) {
					data2 = $.parseJSON(data2);
					if (JSON.stringify(data) === JSON.stringify(data2) ) {
						updateScore($(".task1 .task1-6 .score").text(), "task1-6");
						$(".task1 .task1-6 .passed").show();
					}
					else $(".task1 .task1-6 .failed").show();
					printScore();
					$(".task1-6").fadeIn();
				});
			}).error(function( data ) {
				$(".task1 .task1-6 .failed").show();
				printScore();
				$(".task1-6").fadeIn();
			});
			
			$(".task2").fadeIn();
			
			$.post( URL_TEMA2+"/register.php", { } ).done(function( data ) {
				if (data.localeCompare("username") == 0) {
					updateScore($(".task2 .task2-1 .score").text(), "task2-1");
					$(".task2 .task2-1 .passed").show();
				}
				else $(".task2 .task2-1 .failed").show();
				printScore();
				$(".task2-1").fadeIn();
			}).error(function( data ) {
				$(".task2 .task2-1 .failed").show();
				printScore();
				$(".task2-1").fadeIn();
			});
			
			$.post( URL_TEMA2+"/register.php", { username: "PZujF" } ).done(function( data ) {
				if (data.localeCompare("username") == 0) {
					updateScore($(".task2 .task2-2 .score").text(), "task2-2");
					$(".task2 .task2-2 .passed").show();
				}
				else $(".task2 .task2-2 .failed").show();
				printScore();
				$(".task2-2").fadeIn();
			}).error(function( data ) {
				$(".task2 .task2-2 .failed").show();
				printScore();
				$(".task2-2").fadeIn();
			});
			
			$.post( URL_TEMA2+"/register.php", { username: "PZujF0", password: "wxKLC" } ).done(function( data ) {
				if (data.localeCompare("password") == 0) {
					updateScore($(".task2 .task2-3 .score").text(), "task2-3");
					$(".task2 .task2-3 .passed").show();
				}
				else $(".task2 .task2-3 .failed").show();
				printScore();
				$(".task2-3").fadeIn();
			}).error(function( data ) {
				$(".task2 .task2-3 .failed").show();
				printScore();
				$(".task2-3").fadeIn();
			});
			
			$.post( URL_TEMA2+"/register.php", { username: "PZujF0", password: "wxKLCW1", confirm: "A3X4dx" } ).done(function( data ) {
				if (data.localeCompare("confirm") == 0) {
					updateScore($(".task2 .task2-4 .score").text(), "task2-4");
					$(".task2 .task2-4 .passed").show();
				}
				else $(".task2 .task2-4 .failed").show();
				printScore();
				$(".task2-4").fadeIn();
			}).error(function( data ) {
				$(".task2 .task2-4 .failed").show();
				printScore();
				$(".task2-4").fadeIn();
			});
			
			
			$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_user" } ).done(function( data2 ) {
				var username;
				data2 = $.parseJSON(data2);
				$.each(data2, function(index, value) {
					username = value.usr_username;
					return false;
				});
				$.post( URL_TEMA2+"/register.php", { username: username, password: "wxKLCW1", confirm: "wxKLCW1" } ).done(function( data ) {
					if (data.localeCompare("user_exists") == 0) {
						updateScore($(".task2 .task2-5 .score").text(), "task2-5");
						$(".task2 .task2-5 .passed").show();
					}
					else $(".task2 .task2-5 .failed").show();
					printScore();
					$(".task2-5").fadeIn();
				}).error(function( data ) {
					$(".task2 .task2-5 .failed").show();
					printScore();
					$(".task2-5").fadeIn();
				});
			});
			
			$.post( URL_TEMA2+"/register.php", { username: "PZujF0", password: "wxKLCW1", confirm: "wxKLCW1" } ).done(function( data ) {
				if (data.localeCompare("ok") == 0) {
					var found = false;
					var correctPass = false;
					$.get( URL_TEMA2+"/show-entries.php", { table: "pw_user" } ).done(function( data ) {
						data = $.parseJSON(data);
						$.each(data, function(index, value) {
							if (value.usr_username.localeCompare("PZujF0") == 0) {
								found = true;
								if (CryptoJS.SHA1("wxKLCW1"+value.usr_salt) == value.usr_password)
									correctPass = true;
								return false;
							}
						});
						if (found == true) {
							updateScore($(".task2 .task2-6 .score").text(), "task2-6");
							$(".task2 .task2-6 .passed").show();
						}
						else $(".task2 .task2-6 .failed").show();
						if (correctPass == true) {
							updateScore($(".task2 .task2-8 .score").text(), "task2-8");
							$(".task2 .task2-8 .passed").show();
						}
						else $(".task2 .task2-8 .failed").show();
					});
				}
				else {
					$(".task2 .task2-6 .failed").show();
					$(".task2 .task2-8 .failed").show();
				}
				printScore();
				$(".task2-6").fadeIn();
				$(".task2-8").fadeIn();
			}).error(function( data ) {
				$(".task2 .task2-6 .failed").show();
				$(".task2 .task2-8 .failed").show();
				printScore();
				$(".task2-6").fadeIn();
				$(".task2-8").fadeIn();
			});
			
			$.post( URL_TEMA2+"/register.php", { username: "PZujF0", password: "wxKLCW", confirm: "wxKLCW" } ).done(function( data ) {
				if (data.localeCompare("password_strength") == 0) {
					updateScore($(".task2 .task2-7 .score").text(), "task2-7");
					$(".task2 .task2-7 .passed").show();
				}
				else $(".task2 .task2-7 .failed").show();
				printScore();
				$(".task2-7").fadeIn();
			}).error(function( data ) {
				$(".task2 .task2-7 .failed").show();
				printScore();
				$(".task2-7").fadeIn();
			});
			
			$(".task3").fadeIn();
			
			$.post( URL_TEMA2+"/login.php", { } ).done(function( data ) {
				if (data.localeCompare("username") == 0) {
					updateScore($(".task3 .task3-1 .score").text(), "task3-1");
					$(".task3 .task3-1 .passed").show();
				}
				else $(".task3 .task3-1 .failed").show();
				printScore();
				$(".task3-1").fadeIn();
			}).error(function( data ) {
				$(".task3 .task3-1 .failed").show();
				printScore();
				$(".task3-1").fadeIn();
			});
			
			$.post( URL_TEMA2+"/login.php", { username: "PZujF" } ).done(function( data ) {
				if (data.localeCompare("username") == 0) {
					updateScore($(".task3 .task3-2 .score").text(), "task3-2");
					$(".task3 .task3-2 .passed").show();
				}
				else $(".task3 .task3-2 .failed").show();
				printScore();
				$(".task3-2").fadeIn();
			}).error(function( data ) {
				$(".task3 .task3-2 .failed").show();
				printScore();
				$(".task3-2").fadeIn();
			});
			
			$.post( URL_TEMA2+"/login.php", { username: "PZujF0", password: "wxKLC" } ).done(function( data ) {
				if (data.localeCompare("password") == 0) {
					updateScore($(".task3 .task3-3 .score").text(), "task3-3");
					$(".task3 .task3-3 .passed").show();
				}
				else $(".task3 .task3-3 .failed").show();
				printScore();
				$(".task3-3").fadeIn();
			}).error(function( data ) {
				$(".task3 .task3-3 .failed").show();
				printScore();
				$(".task3-3").fadeIn();
			});
			
			$.post( URL_TEMA2+"/login.php", { username: "wxKLCW", password: "PZujF0" } ).done(function( data ) {
				if (data.localeCompare("user_doesnt_exist") == 0) {
					updateScore($(".task3 .task3-4 .score").text(), "task3-4");
					$(".task3 .task3-4 .passed").show();
				}
				else $(".task3 .task3-4 .failed").show();
				printScore();
				$(".task3-4").fadeIn();
			}).error(function( data ) {
				$(".task3 .task3-4 .failed").show();
				printScore();
				$(".task3-4").fadeIn();
			});
			
			var username;
			var lastLogin;
			$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_user" } ).done(function( data2 ) {
				var password;
				data2 = $.parseJSON(data2);
				$.each(data2, function(index, value) {
					username = value.usr_username;
					password = value.usr_password;
					lastLogin = '0000-00-00 00:00:00';
					return false;
				});
				$.post( URL_TEMA2+"/login.php", { username: username, password: password } ).done(function( data ) {
					if (data.localeCompare("ok") == 0) {
						updateScore($(".task3 .task3-5 .score").text(), "task3-5");
						$(".task3 .task3-5 .passed").show();
					}
					else $(".task3 .task3-5 .failed").show();
					printScore();
					$(".task3-5").fadeIn();
				}).error(function( data ) {
					$(".task3 .task3-5 .failed").show();
					printScore();
					$(".task3-5").fadeIn();
				});
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_user" } ).done(function( data ) {
				var changedLastLogin = false;
				data = $.parseJSON(data);
				$.each(data, function(index, value) {
					if (value.usr_username.localeCompare(username) == 0) {
						found = true;
						var t1 = lastLogin.split(/[- :]/);
						var t2 = value.usr_last_login.split(/[- :]/);
						var d1 = new Date(t1[0], t1[1]-1, t1[2], t1[3], t1[4], t1[5]);
						var d2 = new Date(t2[0], t2[1]-1, t2[2], t2[3], t2[4], t2[5]);
						console.log(d1);
						console.log(d2);
						if (d1 < d2)
							changedLastLogin = true;
						return false;
					}
				});
				if (changedLastLogin == true) {
					updateScore($(".task3 .task3-6 .score").text(), "task3-6");
					$(".task3 .task3-6 .passed").show();
					printScore();
					$(".task3-6").fadeIn();
				}
				else {
					$(".task3 .task3-6 .failed").show();
					printScore();
					$(".task3-6").fadeIn();
				}
			});
			
			$('.task4').fadeIn();
			
			$.get( URL_TEMA2+"/article.php", { } ).done(function( data ) {
				if (data.localeCompare("wrong_art") == 0) {
					updateScore($(".task4 .task4-1 .score").text(), "task4-1");
					$(".task4 .task4-1 .passed").show();
				}
				else $(".task4 .task4-1 .failed").show();
				printScore();
				$(".task4-1").fadeIn();
			}).error(function( data ) {
				$(".task4 .task4-1 .failed").show();
				printScore();
				$(".task4-1").fadeIn();
			});
			
			$.get( URL_TEMA2+"/article.php", { art_id: "PZujF0" } ).done(function( data ) {
				if (data.localeCompare("wrong_art") == 0) {
					updateScore($(".task4 .task4-2 .score").text(), "task4-2");
					$(".task4 .task4-2 .passed").show();
				}
				else $(".task4 .task4-2 .failed").show();
				printScore();
				$(".task4-2").fadeIn();
			}).error(function( data ) {
				$(".task4 .task4-2 .failed").show();
				printScore();
				$(".task4-2").fadeIn();
			});
			
			$.get( URL_TEMA2+"/article.php", { art_id: 120 } ).done(function( data ) {
				if (data.localeCompare("wrong_art") == 0) {
					updateScore($(".task4 .task4-3 .score").text(), "task4-3");
					$(".task4 .task4-3 .passed").show();
				}
				else $(".task4 .task4-3 .failed").show();
				printScore();
				$(".task4-3").fadeIn();
			}).error(function( data ) {
				$(".task4 .task4-3 .failed").show();
				printScore();
				$(".task4-3").fadeIn();
			});
			
			var idArticolIncrement = 0;
			$.get( URL_CHECKER+"/articles.php", { student: STUDENT_ID, bonus: true } ).done(function( data2 ) {
				var article;
				data2 = $.parseJSON(data2);
				$.each(data2, function(index, value) {
					article = value;
					idArticolIncrement = article.id;
					return false;
				});
				$.get( URL_TEMA2+"/article.php", { art_id: article.id } ).done(function( data ) {
					data = $.parseJSON(data);
					if (JSON.stringify(article) === JSON.stringify(data) ) {
						updateScore($(".task4 .task4-4 .score").text(), "task4-4");
						$(".task4 .task4-4 .passed").show();
					}
					else $(".task4 .task4-4 .failed").show();
					printScore();
					$(".task4-4").fadeIn();
				}).error(function( data ) {
					$(".task4 .task4-4 .failed").show();
					printScore();
					$(".task4-4").fadeIn();
				});
				$.get( URL_TEMA2+"/article.php", { art_id: article.id } ).done(function( data ) {
					data = $.parseJSON(data);
					if ((parseInt(article.views) + 1) == parseInt(data.views) ) {
						updateScore($(".task4 .task4-5 .score").text(), "task4-5");
						$(".task4 .task4-5 .passed").show();
					}
					else $(".task4 .task4-5 .failed").show();
					printScore();
					$(".task4-5").fadeIn();
				}).error(function( data ) {
					$(".task4 .task4-5 .failed").show();
					printScore();
					$(".task4-4").fadeIn();
				});
			});
			
			$('.task5').fadeIn();
			
			$.get( URL_TEMA2+"/category.php", { } ).done(function( data ) {
				if (data.localeCompare("wrong_cat") == 0) {
					updateScore($(".task5 .task5-1 .score").text(), "task5-1");
					$(".task5 .task5-1 .passed").show();
				}
				else $(".task5 .task5-1 .failed").show();
				printScore();
				$(".task5-1").fadeIn();
			}).error(function( data ) {
				$(".task5 .task5-1 .failed").show();
				printScore();
				$(".task5-1").fadeIn();
			});
			
			$.get( URL_TEMA2+"/category.php", { cat_id: "PZujF0" } ).done(function( data ) {
				if (data.localeCompare("wrong_cat") == 0) {
					updateScore($(".task5 .task5-2 .score").text(), "task5-2");
					$(".task5 .task5-2 .passed").show();
				}
				else $(".task5 .task5-2 .failed").show();
				printScore();
				$(".task5-2").fadeIn();
			}).error(function( data ) {
				$(".task5 .task5-2 .failed").show();
				printScore();
				$(".task5-2").fadeIn();
			});
			
			$.get( URL_TEMA2+"/category.php", { cat_id: 120 } ).done(function( data ) {
				if (data.localeCompare("wrong_cat") == 0) {
					updateScore($(".task5 .task5-3 .score").text(), "task5-3");
					$(".task5 .task5-3 .passed").show();
				}
				else $(".task5 .task5-3 .failed").show();
				printScore();
				$(".task5-3").fadeIn();
			}).error(function( data ) {
				$(".task5 .task5-3 .failed").show();
				printScore();
				$(".task5-3").fadeIn();
			});
			
			$.get( URL_CHECKER+"/show-entries.php", { student: STUDENT_ID, table: "pw_category" } ).done(function( data2 ) {
				var category;
				data2 = $.parseJSON(data2);
				$.each(data2, function(index, value) {
					category = value.cat_id;
					return false;
				});
				$.get( URL_CHECKER+"/article-categories.php", { student: STUDENT_ID } ).done(function( data3 ) {
					var idArticles = [];
					data3 = $.parseJSON(data3);
					$.each(data3, function(index, value) {
						if (value.artc_cat_id == category) idArticles.push(value.artc_art_id);
					});
					$.get( URL_CHECKER+"/articles.php", { student: STUDENT_ID, bonus: true } ).done(function( data4 ) {
						var articles = [];
						data4 = $.parseJSON(data4);
						$.each(data4, function(index, value) {
							if (value.id == idArticolIncrement) value.views = (parseInt(value.views)+2).toString();
							if (idArticles.indexOf(value.id) != -1) articles.push(value);
						});
						$.get( URL_TEMA2+"/category.php", { cat_id: category } ).done(function( data ) {
							data = $.parseJSON(data);
							if (JSON.stringify(articles) === JSON.stringify(data) ) {
								updateScore($(".task5 .task5-4 .score").text(), "task5-4");
								$(".task5 .task5-4 .passed").show();
							}
							else $(".task5 .task5-4 .failed").show();
							printScore();
							$(".task5-4").fadeIn();
						}).error(function( data ) {
							$(".task5 .task5-4 .failed").show();
							printScore();
							$(".task5-4").fadeIn();
						});
					});
				});
			});
			
			$('.task6').fadeIn();
			
			$.get( URL_TEMA2+"/search.php", { } ).done(function( data ) {
				if (data.localeCompare("s") == 0) {
					updateScore($(".task6 .task6-1 .score").text(), "task6-1");
					$(".task6 .task6-1 .passed").show();
				}
				else $(".task6 .task6-1 .failed").show();
				printScore();
				$(".task6-1").fadeIn();
			}).error(function( data ) {
				$(".task6 .task6-1 .failed").show();
				printScore();
				$(".task6-1").fadeIn();
			});
			
			$.get( URL_TEMA2+"/search.php", { s: "" } ).done(function( data ) {
				if (data.localeCompare("s") == 0) {
					updateScore($(".task6 .task6-2 .score").text(), "task6-2");
					$(".task6 .task6-2 .passed").show();
				}
				else $(".task6 .task6-2 .failed").show();
				printScore();
				$(".task6-2").fadeIn();
			}).error(function( data ) {
				$(".task6 .task6-2 .failed").show();
				printScore();
				$(".task6-2").fadeIn();
			});
			
			var artForCart = 0;
			var searchTerm;
			$.get( URL_CHECKER+"/articles.php", { student: STUDENT_ID, bonus: true } ).done(function( data2 ) {
				data2 = $.parseJSON(data2);
				$.each(data2, function(index, value) {
					searchTerm = value.title.substr(0,3).trim();
					artForCart = value.id;
					return false;
				});
				var articles = [];
				$.each(data2, function(index, value) {
					if (value.id == idArticolIncrement) value.views = (parseInt(value.views)+2).toString();
					if (value.title.indexOf(searchTerm) != -1 || value.content.indexOf(searchTerm) != -1) articles.push(value);
				});
				$.get( URL_TEMA2+"/search.php", { s: searchTerm } ).done(function( data ) {
					data = $.parseJSON(data);
					if (JSON.stringify(articles) === JSON.stringify(data) ) {
						updateScore($(".task6 .task6-3 .score").text(), "task6-3");
						$(".task6 .task6-3 .passed").show();
					}
					else $(".task6 .task6-3 .failed").show();
					printScore();
					$(".task6-3").fadeIn();
				}).error(function( data ) {
					$(".task6 .task6-3 .failed").show();
					printScore();
					$(".task6-3").fadeIn();
				});
			});
			
			var searchTermOld = searchTerm;
			$.get( URL_CHECKER+"/articles.php", { student: STUDENT_ID, bonus: true } ).done(function( data2 ) {
				data2 = $.parseJSON(data2);
				$.each(data2, function(index, value) {
					searchTerm = value.content.trim().split(' ');
					searchTerm = searchTerm[0];
					return false;
				});
				var articles = [];
				$.each(data2, function(index, value) {
					if (value.id == idArticolIncrement) value.views = (parseInt(value.views)+2).toString();
					if (value.title.indexOf(searchTerm) != -1 || value.content.indexOf(searchTerm) != -1) articles.push(value);
				});
				$.get( URL_TEMA2+"/search.php", { s: searchTerm } ).done(function( data ) {
					data = $.parseJSON(data);
					if (JSON.stringify(articles) === JSON.stringify(data) ) {
						updateScore($(".task6 .task6-4 .score").text(), "task6-4");
						$(".task6 .task6-4 .passed").show();
					}
					else $(".task6 .task6-4 .failed").show();
					printScore();
					$(".task6-4").fadeIn();
				}).error(function( data ) {
					$(".task6 .task6-4 .failed").show();
					printScore();
					$(".task6-4").fadeIn();
				});
			});
			
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_article_category" } ).done(function( data ) {
				var categoryId = 0;
				data = $.parseJSON(data);
				$.each(data, function(index, value) {
					if (value.artc_art_id == artForCart) {
						categoryId = value.artc_cat_id;
						return false;
					}
				});
				$.get( URL_TEMA2+"/category.php", { cat_id: categoryId } ).done(function( data ) {
					var articles = [];
					data = $.parseJSON(data);
					$.each(data, function(index, value) {
						if (value.title.indexOf(searchTermOld) != -1 || value.content.indexOf(searchTermOld) != -1) articles.push(value);
					});
					$.get( URL_TEMA2+"/search.php", { s: searchTermOld, cat_id: categoryId } ).done(function( data ) {
						data = $.parseJSON(data);
						if (JSON.stringify(articles) === JSON.stringify(data) ) {
							updateScore($(".task6 .task6-5 .score").text(), "task6-5");
							$(".task6 .task6-5 .passed").show();
						}
						else $(".task6 .task6-5 .failed").show();
						printScore();
						$(".task6-5").fadeIn();
					}).error(function( data ) {
						$(".task6 .task6-5 .failed").show();
						printScore();
						$(".task6-5").fadeIn();
					});
				}).error(function( data ) {
					$(".task6 .task6-5 .failed").show();
					printScore();
					$(".task6-5").fadeIn();
				});
			}).error(function( data ) {
				$(".task6 .task6-5 .failed").show();
				printScore();
				$(".task6-5").fadeIn();
			});
			
			$('.task7').fadeIn();
			
			$.post( URL_TEMA2+"/edit-article.php", { } ).done(function( data ) {
				if (data.localeCompare("id") == 0) {
					updateScore($(".task7 .task7-1 .score").text(), "task7-1");
					$(".task7 .task7-1 .passed").show();
				}
				else $(".task7 .task7-1 .failed").show();
				printScore();
				$(".task7-1").fadeIn();
			}).error(function( data ) {
				$(".task7 .task7-1 .failed").show();
				printScore();
				$(".task7-1").fadeIn();
			});
			
			$.post( URL_TEMA2+"/edit-article.php", { id: "PZujF0" } ).done(function( data ) {
				if (data.localeCompare("id") == 0) {
					updateScore($(".task7 .task7-2 .score").text(), "task7-2");
					$(".task7 .task7-2 .passed").show();
				}
				else $(".task7 .task7-2 .failed").show();
				printScore();
				$(".task7-2").fadeIn();
			}).error(function( data ) {
				$(".task7 .task7-2 .failed").show();
				printScore();
				$(".task7-2").fadeIn();
			});
			
			$.post( URL_TEMA2+"/edit-article.php", { id: 1 } ).done(function( data ) {
				if (data.localeCompare("title") == 0) {
					updateScore($(".task7 .task7-3 .score").text(), "task7-3");
					$(".task7 .task7-3 .passed").show();
				}
				else $(".task7 .task7-3 .failed").show();
				printScore();
				$(".task7-3").fadeIn();
			}).error(function( data ) {
				$(".task7 .task7-3 .failed").show();
				printScore();
				$(".task7-3").fadeIn();
			});
			
			$.post( URL_TEMA2+"/edit-article.php", { id: 1, title: "PZujF0 wxKLCW" } ).done(function( data ) {
				if (data.localeCompare("content") == 0) {
					updateScore($(".task7 .task7-4 .score").text(), "task7-4");
					$(".task7 .task7-4 .passed").show();
				}
				else $(".task7 .task7-4 .failed").show();
				printScore();
				$(".task7-4").fadeIn();
			}).error(function( data ) {
				$(".task7 .task7-4 .failed").show();
				printScore();
				$(".task7-4").fadeIn();
			});
			
			$.post( URL_TEMA2+"/edit-article.php", { id: 1, title: "PZujF0 wxKLCW", content: "ILEn3o oU9Ft6oU5 swUO0 CMX JSPhBAWZE T2f2I 87Dep5Kk Krwxpvghl TVuSzO C3NlMWsq SwVc FEYd3t lO2eKw klS pGhcDKCNC JPAo yCx26T 97BFeV17 qN9CqTfew XlYmP Ymy5gp n1UC VJOlxYYXS bpB8 zvz6tWEz 4NA5 d2DXRYu XrIaD7MM mhrtLo8kB 7biP ksmcr 2oiLzVTm LJZdcKB 4dwco 2Nau9mW0 li9Ue hVO U1c DwKQ3Wf Y32tcopdN vWFKZWFO AQ8gtF0kI AAVDCpQ1O Ozz fjLcZz8A hQTXQ FNOg rT8iUXlJ UuMegY P7Nf E9mvn ich Eba 58hOFcjsq qEpysFX OjB lUoD 2O7ZUfgJU 2mUCNy l0H 7vDII D6CA9rH8l p4QS7dMJ0 MmmtF ZjcHiQ UqXl75G3 LUnS7a 8wovSSa StzAM oGPm2 rJ0WuUkm2 Zb0nGT Rf8l I7d7O2tQ Vz0R4VbqY q9GOQA4 Pd2DWaR YTx TsoTksPw NcjWT7Mtc ipxWlH pFHWtBoR Jkkfd7 w4lERP l8fS4AzS fAWJbkBG3 1j88LFd7j W9q pj9 T20 CWR hsulnvEw qbRxvWt ny4GI4z 4Hn0ybi1 DpbiVQI IfC Jh2hlI0 hLuY8 xjNzZq bJU1r2KGF pWrHi HIqs pBHX vwUWv5Fq7 sRN gd4 VmQD4h5 HHYE ubwqHB5 IcA 0IQdNx8 oLeG vnyu2aYeG Wiu41 EBHnrUa 3knPy4G3s xvqw 7VGppKr6 2OMtI tLhRAPVhT xrTXX 4Sjui4W tYdgs dVIuMjkIA 68E0 CDa XFN1Bd ArL2nY 6tKpNt01z Fze dpNa5 cGPHhgt ErhKV 9Jv K5iq wISWw21 fIX ZdqjSSBCN Mw9Whfe ULqMIWP 44r11qfs 7klK8ZwF tWoI it44c1T 5Xn7ZNmsy MTeVSL 1eypWcH hLCiE oCUvCI 4gmR9AN2l 3AWsw aWqV JA67d1 PJvU0SM szcO fpUIV3SRu qdoxlCyY htmhm8 PIEDGT ACY uQ8iglH GjlFLD98 vhnkZ1YFV gxZ 2P3k6p2U6 gL7UU Pqwc weIc9KsH nJzr4GQ6 WsRIzLD B3lOOR2x chw 1TDAkIgbO 8gJQQvtE7 0VlRYS b9r5akILF 2RfUZw Qm9k1gR cdS 5Nlf qqz9 fAe6 96mNWJXg e8LqlDBr" } ).done(function( data ) {
				if (data.localeCompare("author") == 0) {
					updateScore($(".task7 .task7-5 .score").text(), "task7-5");
					$(".task7 .task7-5 .passed").show();
				}
				else $(".task7 .task7-5 .failed").show();
				printScore();
				$(".task7-5").fadeIn();
			}).error(function( data ) {
				$(".task7 .task7-5 .failed").show();
				printScore();
				$(".task7-5").fadeIn();
			});
			
			$.post( URL_TEMA2+"/edit-article.php", { id: 1, title: "PZujF0 wxKLCW", content: "ILEn3o oU9Ft6oU5 swUO0 CMX JSPhBAWZE T2f2I 87Dep5Kk Krwxpvghl TVuSzO C3NlMWsq SwVc FEYd3t lO2eKw klS pGhcDKCNC JPAo yCx26T 97BFeV17 qN9CqTfew XlYmP Ymy5gp n1UC VJOlxYYXS bpB8 zvz6tWEz 4NA5 d2DXRYu XrIaD7MM mhrtLo8kB 7biP ksmcr 2oiLzVTm LJZdcKB 4dwco 2Nau9mW0 li9Ue hVO U1c DwKQ3Wf Y32tcopdN vWFKZWFO AQ8gtF0kI AAVDCpQ1O Ozz fjLcZz8A hQTXQ FNOg rT8iUXlJ UuMegY P7Nf E9mvn ich Eba 58hOFcjsq qEpysFX OjB lUoD 2O7ZUfgJU 2mUCNy l0H 7vDII D6CA9rH8l p4QS7dMJ0 MmmtF ZjcHiQ UqXl75G3 LUnS7a 8wovSSa StzAM oGPm2 rJ0WuUkm2 Zb0nGT Rf8l I7d7O2tQ Vz0R4VbqY q9GOQA4 Pd2DWaR YTx TsoTksPw NcjWT7Mtc ipxWlH pFHWtBoR Jkkfd7 w4lERP l8fS4AzS fAWJbkBG3 1j88LFd7j W9q pj9 T20 CWR hsulnvEw qbRxvWt ny4GI4z 4Hn0ybi1 DpbiVQI IfC Jh2hlI0 hLuY8 xjNzZq bJU1r2KGF pWrHi HIqs pBHX vwUWv5Fq7 sRN gd4 VmQD4h5 HHYE ubwqHB5 IcA 0IQdNx8 oLeG vnyu2aYeG Wiu41 EBHnrUa 3knPy4G3s xvqw 7VGppKr6 2OMtI tLhRAPVhT xrTXX 4Sjui4W tYdgs dVIuMjkIA 68E0 CDa XFN1Bd ArL2nY 6tKpNt01z Fze dpNa5 cGPHhgt ErhKV 9Jv K5iq wISWw21 fIX ZdqjSSBCN Mw9Whfe ULqMIWP 44r11qfs 7klK8ZwF tWoI it44c1T 5Xn7ZNmsy MTeVSL 1eypWcH hLCiE oCUvCI 4gmR9AN2l 3AWsw aWqV JA67d1 PJvU0SM szcO fpUIV3SRu qdoxlCyY htmhm8 PIEDGT ACY uQ8iglH GjlFLD98 vhnkZ1YFV gxZ 2P3k6p2U6 gL7UU Pqwc weIc9KsH nJzr4GQ6 WsRIzLD B3lOOR2x chw 1TDAkIgbO 8gJQQvtE7 0VlRYS b9r5akILF 2RfUZw Qm9k1gR cdS 5Nlf qqz9 fAe6 96mNWJXg e8LqlDBr", author: 1 } ).done(function( data ) {
				if (data.localeCompare("cat_id") == 0) {
					updateScore($(".task7 .task7-6 .score").text(), "task7-6");
					$(".task7 .task7-6 .passed").show();
				}
				else $(".task7 .task7-6 .failed").show();
				printScore();
				$(".task7-6").fadeIn();
			}).error(function( data ) {
				$(".task7 .task7-6 .failed").show();
				printScore();
				$(".task7-6").fadeIn();
			});
			
			var artId = Math.floor((Math.random()*3)+1);
			var artUpdateDate = '';
			$.get( URL_TEMA2+"/show-entries.php", { table: "pw_article" }, function(data) {
				data = $.parseJSON(data);
				var author = 0, oldAuthor = 0, cat1 = 0, cat2 = 0, authorUsername;
				$.each(data, function(index, value) {
					if (value.art_id == artId) {
						oldAuthor = value.art_author;
						artUpdateDate = value.art_update_date;
						return false;
					}
				});
				do {
					author = Math.floor((Math.random()*3)+1);
				} while (author == oldAuthor);
				cat1 = Math.floor((Math.random()*3)+1);
				do {
					cat2 = Math.floor((Math.random()*3)+1);
				} while (cat1 == cat2);
				$.get( URL_TEMA2+"/show-entries.php", { table: "pw_user" }, function(data) {
					data = $.parseJSON(data);
					$.each(data, function(index, value) {
						if (value.usr_id == author) {
							authorUsername = value.usr_username;
							return false;
						}
					});
				});
				cats = []; cats.push(cat1); cats.push(cat2);
				$.post( URL_TEMA2+"/edit-article.php", { id: artId, title: "PZujF0 wxKLCW", content: "ILEn3o oU9Ft6oU5 swUO0 CMX JSPhBAWZE T2f2I 87Dep5Kk Krwxpvghl TVuSzO C3NlMWsq SwVc FEYd3t lO2eKw klS pGhcDKCNC JPAo yCx26T 97BFeV17 qN9CqTfew XlYmP Ymy5gp n1UC VJOlxYYXS bpB8 zvz6tWEz 4NA5 d2DXRYu XrIaD7MM mhrtLo8kB 7biP ksmcr 2oiLzVTm LJZdcKB 4dwco 2Nau9mW0 li9Ue hVO U1c DwKQ3Wf Y32tcopdN vWFKZWFO AQ8gtF0kI AAVDCpQ1O Ozz fjLcZz8A hQTXQ FNOg rT8iUXlJ UuMegY P7Nf E9mvn ich Eba 58hOFcjsq qEpysFX OjB lUoD 2O7ZUfgJU 2mUCNy l0H 7vDII D6CA9rH8l p4QS7dMJ0 MmmtF ZjcHiQ UqXl75G3 LUnS7a 8wovSSa StzAM oGPm2 rJ0WuUkm2 Zb0nGT Rf8l I7d7O2tQ Vz0R4VbqY q9GOQA4 Pd2DWaR YTx TsoTksPw NcjWT7Mtc ipxWlH pFHWtBoR Jkkfd7 w4lERP l8fS4AzS fAWJbkBG3 1j88LFd7j W9q pj9 T20 CWR hsulnvEw qbRxvWt ny4GI4z 4Hn0ybi1 DpbiVQI IfC Jh2hlI0 hLuY8 xjNzZq bJU1r2KGF pWrHi HIqs pBHX vwUWv5Fq7 sRN gd4 VmQD4h5 HHYE ubwqHB5 IcA 0IQdNx8 oLeG vnyu2aYeG Wiu41 EBHnrUa 3knPy4G3s xvqw 7VGppKr6 2OMtI tLhRAPVhT xrTXX 4Sjui4W tYdgs dVIuMjkIA 68E0 CDa XFN1Bd ArL2nY 6tKpNt01z Fze dpNa5 cGPHhgt ErhKV 9Jv K5iq wISWw21 fIX ZdqjSSBCN Mw9Whfe ULqMIWP 44r11qfs 7klK8ZwF tWoI it44c1T 5Xn7ZNmsy MTeVSL 1eypWcH hLCiE oCUvCI 4gmR9AN2l 3AWsw aWqV JA67d1 PJvU0SM szcO fpUIV3SRu qdoxlCyY htmhm8 PIEDGT ACY uQ8iglH GjlFLD98 vhnkZ1YFV gxZ 2P3k6p2U6 gL7UU Pqwc weIc9KsH nJzr4GQ6 WsRIzLD B3lOOR2x chw 1TDAkIgbO 8gJQQvtE7 0VlRYS b9r5akILF 2RfUZw Qm9k1gR cdS 5Nlf qqz9 fAe6 96mNWJXg e8LqlDBr", author: author, cat_id: cats } ).done(function( data2 ) {
					if (data2.localeCompare("ok") == 0) {
						$.get( URL_TEMA2+"/show-entries.php", { table: "pw_article_category" }, function(data3) {
							var legaturi = $.parseJSON(data3);
							var este = true;
							$.each(legaturi, function(index, value) {
								if ((value.artc_cat_id == cat1 || value.artc_cat_id == cat2) && value.artc_art_id == artId)
								{
									updateScore($(".task7 .task7-7 .score").text(), "task7-7");
									$(".task7 .task7-7 .passed").show();
									este = true;
									return false;
								}
							});
							if (!este) $(".task7 .task7-7 .failed").show();
						});
						$.get( URL_TEMA2+"/article.php", { art_id: artId }, function(data3) {
							var article = $.parseJSON(data3);
							if (article.author.localeCompare(authorUsername) == 0)
							{
								updateScore($(".task7 .task7-8 .score").text(), "task7-8");
								$(".task7 .task7-8 .passed").show();
							}
							else $(".task7 .task7-8 .failed").show();
							var t1 = artUpdateDate.split(/[- :]/);
							var t2 = article.update_date.split(/[- :]/);
							var d1 = new Date(t1[0], t1[1]-1, t1[2], t1[3], t1[4], t1[5]);
							var d2 = new Date(t2[0], t2[1]-1, t2[2], t2[3], t2[4], t2[5]);
							console.log(d1);
							console.log(d2);
							if (d1 < d2)
							{
								updateScore($(".task7 .task7-10 .score").text(), "task7-10");
								$(".task7 .task7-10 .passed").show();
							}
							else $(".task7 .task7-10 .failed").show();
						});
						$.get( URL_TEMA2+"/search.php", { s: "PZujF0" }, function(data3) {
							var articles = $.parseJSON(data3);
							var este = true;
							$.each(articles, function(index, value) {
								if (value.id == artId)
								{
									updateScore($(".task7 .task7-9 .score").text(), "task7-9");
									$(".task7 .task7-9 .passed").show();
									este = true;
									return false;
								}
							});
							if (!este) $(".task7 .task7-9 .failed").show();
						});
					}
					else {
						$(".task7 .task7-7 .failed").show();
						$(".task7 .task7-8 .failed").show();
						$(".task7 .task7-9 .failed").show();
						$(".task7 .task7-10 .failed").show();
					}
					printScore();
					$(".task7-7").fadeIn();
					$(".task7-8").fadeIn();
					$(".task7-9").fadeIn();
					$(".task7-10").fadeIn();
				}).error(function( data ) {
					$(".task7 .task7-7 .failed").show();
					$(".task7 .task7-8 .failed").show();
					$(".task7 .task7-9 .failed").show();
					$(".task7 .task7-10 .failed").show();
					printScore();
					$(".task7-7").fadeIn();
					$(".task7-8").fadeIn();
					$(".task7-9").fadeIn();
					$(".task7-10").fadeIn();
				});
			});
			
		}
		
		var checkAll = function() {
			$(".task, .task .passed, .task .failed").hide();
			tasks();
		}
		
		var updateScore = function(add, task) {
			//console.log('Adaug '+add+' de la task-ul '+task);
			score += parseFloat(add);
		}
		
		var printScore = function() {
			$("#total-score").text(parseFloat(score).toFixed(2));
		}
		
		return checkAll();
		
	}
	
	$("#check-now").on("click",function() { checker(); });
});