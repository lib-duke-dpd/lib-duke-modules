<?php

?>

<div class="searchBoxContent" id="databasesTabContent" style="display:none">
	<div class="tabContentUpper">
		<!-- DB-Finder interface: -->
		<form action="http://db.library.duke.edu/search" method="get" name="findDatabases">
			<!-- HIDDEN input fields -->
			<input type="hidden" name="Nty" value="1" />
			<input type="hidden" name="N" value="0" />
		
			<p class="searchOptionsPrimary">
				<select id="databasecodeinput" name="Ntk">
					<option selected="selected" value="Keyword">Keywords</option>
					<option value="Title">Title</option>
					<option value="Subject">Subject Heading</option>
				</select>
				<input class="hasHint styledSearchBox" name="Ntt" size="38" title="Search for databases by title &amp; subject" type="text" value="" />
				<input class="styledSearchButton" alt="Enter a search term and click on 'Search' to get database results" onclick="pageTracker._trackEvent('homepageSearchBox', 'databasesSearch');" type="submit" value="Search" />
				<input class="styledSearchButton_small" alt="Enter a search term and click on 'Go' to get database results" onclick="pageTracker._trackEvent('homepageSearchBox', 'databasesSearch');" type="submit" value="GO" />
			</p>
		</form>
		<p class="whatSearch">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'whatIsDatabasesSearch');" href="javascript:unhide('whatDatabases');"><strong>About Databases</strong></a>
		</p>
	</div> <!-- /tabContentUpper -->
	<div class="toggleClosed" id="whatDatabases">
		<p><strong>What am I searching when I use the Databases tab?</strong></p>
		<ul>
			<li>Collections of articles or other materials, often in a specific subject area (e.g., <em>Academic Search Premier,</em> <em>Web of Science,</em> <em>JSTOR,</em> <em>PsycInfo</em>)</li>
		</ul>
		<p><strong>Search tips:</strong></p>
		<ul>
			<li>Start here to connect to databases, but do NOT use this tab search for specific articles within the databases</li>
			<li>For help finding an appropriate database, refer to our <a href="http://library.duke.edu/research/subject/index.html">Research Guides</a></li>
		</ul>
		<p>
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'learnDatabases');" href="http://library.duke.edu/research/help/databases/">Learn more at the Articles &#038; Databases page >></a>
		</p>
		<div class="closeWhat">
			<div class="closeWhatButton">
				<a onclick="pageTracker._trackEvent('homepageSearchBox', 'closeWhat');" href="javascript:unhide('whatDatabases');">&#160;Close X&#160;</a>
			</div>
		</div>
	</div>
	<div class="tabContentLower">	
		<p class="searchOptionsTertiary">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'databasesSubject');" href="http://library.duke.edu/metasearch/db/subject/">Find Databases by Subject</a> &nbsp;|&nbsp; <a onclick="pageTracker._trackEvent('homepageSearchBox', 'databasesTrial');" href="http://library.duke.edu/apps/dbtrials/">Trial Databases</a>
		</p>
	</div> <!-- /tabContentLower -->
</div> <!-- /databasesTabContent -->
