var currentTabClass = "currentSearchTab";
var tabContentSuffix = "Content";

function activateTab(tabLink) {
	tab = tabLink.parentNode;
	if (tab.className != currentTabClass) { // not already current tab
		// find current tab
		var currentTab;
		var tabList = tab.parentNode.childNodes;
		for (var i=0; i < tabList.length; i++) {
			if (tabList[i].className == currentTabClass) {
				currentTab = tabList[i];
				break;
			}
		}
		// get content node for current tab
		var	currentTabContent = document.getElementById(currentTab.id + tabContentSuffix);
		// turn off current tab and content
		//currentTab.setAttribute("class", "");
		currentTab.className = "";
		currentTabContent.style.display = 'none';	
		// turn on new tab
		//tab.setAttribute("class", currentTabClass);
		tab.className = currentTabClass;
		document.getElementById(tab.id + tabContentSuffix).style.display = 'block';
	}
}
