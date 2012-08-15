<?php

?>
<div class="searchBoxContent" id="ejournalsTabContent" style="display:none">
	<div class="tabContentUpper">
		<form action="http://getitatduke.library.duke.edu/" method="get" name="findjournals">
			<!-- HIDDEN input elements -->
			<input name="V" type="hidden" value="1.0" />
			<input name="tab" type="hidden" value="JOURNALS" />
			<input name="L" type="hidden" value="PM6MT7VG3J" />

			<p class="searchOptionsPrimary">
				<select id="ejournalcodeinput" name="S">
					<option selected="selected" value="T_W_A">Title</option>
					<option value="AC_T_B">Title Starts With</option>
					<option value="AC_T_M">Exact Title</option>
					<option value="I_M">ISSN</option>
				</select>
				<input class="hasHint styledSearchBox" id="journals-query" name="C" size="38" title="Search for online journals by title" type="text" value="" />
				<input class="styledSearchButton" alt="Enter a search term and click on 'Search' to get journal title results" id="submit" onclick="pageTracker._trackEvent('homepageSearchBox', 'ejournalsSearch');" type="submit" value="Search" />
				<input class="styledSearchButton_small" alt="Enter a search term and click on 'Go' to get journal title results" id="submit" onclick="pageTracker._trackEvent('homepageSearchBox', 'ejournalsSearch');" type="submit" value="GO" />
			</p>
		</form>
		<p class="whatSearch">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'whatIsEjournalsSearch');" href="javascript:unhide('whatJournals');"><strong>About eJournal Titles</strong></a>
		</p>
	</div> <!-- /tabContentUpper -->
	<div class="toggleClosed" id="whatJournals">
		<p><strong>What am I searching when I use the eJournal Titles tab?</strong></p>
		<ul>
			<li>Journal titles available online through Duke University Libraries (e.g., <em>Lancet,</em> <em>Journal of Neuroscience,</em> <em>Child Development</em>)</li>
		</ul>
		<p><strong>Search tips:</strong></p>
		<ul>
			<li>Click the link for the dates you want to get to specific articles</li>
			<li>Start here to connect to online journals, but do NOT use this tab to search for specific articles within the journals</li>
		</ul>
		<p>
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'learnejournals');" href="http://library.duke.edu/research/finding/journal.html">Learn more at the How to Find Journals page >></a>
		</p>
		<div class="closeWhat">
			<div class="closeWhatButton">
				<a onclick="pageTracker._trackEvent('homepageSearchBox', 'closeWhat');" href="javascript:unhide('whatJournals');">&#160;Close X&#160;</a>
			</div>
		</div>
	</div>
	<div class="tabContentLower">
		<p class="searchOptionsTertiary">
			<a onclick="pageTracker._trackEvent('homepageSearchBox', 'ejournalsAdvanced');" href="http://library.duke.edu/metasearch/ej/">Browse e-journals by title</a>
		</p>
	</div> <!-- /tabContentLower -->
</div> <!-- /ejournalsTabContent -->
