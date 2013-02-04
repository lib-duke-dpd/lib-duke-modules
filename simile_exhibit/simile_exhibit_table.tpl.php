<div class="dataCollectionView"> 

	<div ex:role="viewPanel" ex:formats="date {template: 'MMM d, yyyy'}"> 
		<div ex:role="view"
		   ex:orders=".subject,.label"
		   ex:directions="ascending"
		   ex:possibleOrders=".subject, .label, .format, .idno" ></div> 
	 
	  <div ex:role="lens"> 
	  	<div class="dataCollectionBox"> 
	 			<div class="titleBox">
		 			<span class="title" ex:content=".label"></span>
	    	</div> 
				<div class="details">
					<div class="detailsBox">
						<div class="url"><a ex:content=".address" ex:href-content=".address"></a></div>			  
						<div class="row" ex:if-exists=".abstract" ex:content=".abstract"></div>
						<div ex:if-exists=".subject" class="row">
							<span class="caption" >Subject:</span> 
							<span ex:content=".subject" class="text"></span> 
						</div>
						<div ex:if-exists=".format" class="row">
							<span class="caption" >Format:</span> 
							<span ex:if-exists=".format" ex:content=".format" class="text"></span> 
						</div>
						<div ex:if-exists=".keywords" class="row">
							<span class="caption" >Keywords:</span> 
							<span ex:content=".keywords" class="text"></span> 
						</div>
						<div class="clear"></div>
	       	</div>
				</div>
	 		</div> 
	  </div> 
	</div> 
</div>

