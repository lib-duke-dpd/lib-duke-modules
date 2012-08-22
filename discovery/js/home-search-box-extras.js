/* the function changeCatalogFunc() is intended to manipulate the form input values for the catalog search form so that searching *and* browsing are available form a asingle form.  It takes a passed-in select element, and changes that element's name to either find_code or scan_code, and changes the names and/or values of its fellow form elements ("func" and "request/scan_start") so that the approrpiate type fo search can be conducted. */
function changeCatalogFunc(selectInput) {
	var funcInput = document.getElementById("catalogfuncinput");
	var queryInput = document.getElementById("catalogqueryinput");
	if ((funcInput != null) && (queryInput != null) && (selectInput != null)) {
		// three objectives: change the select element's name between "scan_code" (browsing) and "find_code" (searching, depending on the option value selected, and change the corresponding "func" value to "scan" or "find-b", and the corresponding query input's name from "request" to "scan_start".
		var selectInputValue = selectInput.options[selectInput.selectedIndex].value;
		if ((selectInputValue == "TIT") || (selectInputValue == "AUT") || (selectInputValue == "SUB")) {
			selectInput.name = "scan_code";
			funcInput.value = "scan";
			queryInput.name = "scan_start";
		} else {
			selectInput.name = "find_code";
			funcInput.value = "find-b";
			queryInput.name = "request";
		}
	}
}