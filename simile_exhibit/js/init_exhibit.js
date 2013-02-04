(function($){
	Drupal.behaviors.simile_exhibit = {
		attach: function(context, settings) {
			var fDone = function() {
				var params = SimileAjax.parseURLParameters();
				var options = ["keywords", "format", "subject","label"];
				for ( var i in options ) {
					var option = options[i];
					if (option in params) {
						if (params[option]) {
							$('#' + option + "-facet").attr("ex:selection", params[option]);
						}
						else {
							$('#' + option + "-facet").attr("ex:selectMissing", "true");
						}
					}
				}
				window.exhibit = Exhibit.create();
				window.exhibit.configureFromDOM();
			};
			window.database = Exhibit.Database.create();
			window.database.loadDataLinks(fDone);
			
			$('li#collections a').addClass('current');
			$('#right-sidebar li#browse a').addClass('current');
			$('.titleBox').live('click', function() {
				$(this).next('.details').slideToggle('fast');
			});
			$('.masterToggle').live('click', function() {
				$('.details').slideToggle('fast');
			});
			
			// This code comes from "library.duke.edu/javascript/main/tabs-and-rightnav-highlight.js"
			var url = $.url();
			var tabFolder = url.segment(2);
			var file = url.attr('file');
			$('#nav li').each(function(){
				if ($(this).attr('id') == tabFolder) {
					$(this).children('a').addClass('current');
				}
			});
			$('#right-sidebar li a').each(function() {
				if ($(this).attr('href') == file || $(this).attr('href') == url) {
					$(this).addClass('current');
				}
			});
			
			// This code comes from "library.duke.edu/javascript/main/right-nav-accordian.js"
			$('ul.browse ul').hide();
			$.each($('ul.browse'), function(){
				$('#' + this.id + '.expandfirst ul:first').show();
				$('ul.browse li').removeClass().addClass("collapse");
			});
			$('ul.browse li a.heading').click(function() {
				var parent = this.parentNode;
				$(this).siblings('ul').slideToggle('fast');
				if($(parent).hasClass('expand')){
					$(parent).removeClass().addClass("collapse");
				} else {
					$(parent).removeClass().addClass("expand");
				}
				return false;
			}); 	
		}
	}
})(jQuery);