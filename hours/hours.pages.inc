<?php

function hours_view_hours() {
	return t('This is a beautiful representation of what will become the <strong>Hour Table</strong> page.');
}

function hours_view_calendar($calData) {
	#return t('<p>You requested the ' . $calData['calendar'] . ' library.</p>');
    #return theme('hours_monthview', array('calendar' => $calData));
    $render = array(
        '#type' => 'markup',
        '#markup' => t('<p>You requested the ' . $calData['calendar'] . ' library.</p>'),
    );
    return $render;
}
