function unhide(divID) {
	var item = document.getElementById(divID);
	if (item) {
		item.className=(item.className=='toggleClosed')?'toggleOpen':'toggleClosed';
	}
}

(function($) {
	Drupal.behaviors.discovery = {
		attach: function(context, settings) {
			$('input.hasHint').focus(function() {
				if ($(this).val() == "" || $(this).val() == $(this).attr('title')){
					$(this).val("").removeClass("hinted");
				}
			}).blur(function() {
				if ($(this).val() == "") {
					$(this).val($(this).attr('title')).addClass("hinted");
				}
			}).filter(function() {
				if ($(this).val() == "" || $(this).val() == $(this).attr('title')){
					$(this).val(jQuery(this).attr('title')).addClass("hinted");
				}
			});
			
			$('form').submit(function() {
				if ($("input:text", this).val() == $("input:text", this).attr('title')) {
					$("input:text", this).val("");
				}
			});
			
			$('INPUT.styledSearchButton').click(function(evt){
				pageTracker._trackEvent('homepageSearchBox', 'allSearch');
				var bookreview_bool = !($('#check_bookreviews').is(':checked'));
				var newspaper_bool = !($('#check_newspaper').is(':checked'));
				$('#summon_bookreviews').attr('checked', bookreview_bool);
				$('#summon_newspaper').attr('checked', newspaper_bool);
			});

			var catalogAutoSuggestInputIDsObject = {
				suggestUrl: "http://autosuggest.trln.org/suggestservice/",
				indexInput: "#catalogcodeinput",
				sourceInput: "#catalogsource",
				suggestionFlagInput: "#catalogsuggestions",
				queryForm: "form[name='searchCatalog']",
				querySubmit: "#catalogsubmit"
			}; // clearIndexOnFirstFocus: true, clearIndexOnFirstChange: false (for auto-focus forms)
			if ($('#catalogqueryinput').size() > 0) {
				console.log($('#catalogqueryinput'));
			}
			$("#catalogqueryinput").autosuggest(catalogAutoSuggestInputIDsObject);

		}
	};
})(jQuery);
