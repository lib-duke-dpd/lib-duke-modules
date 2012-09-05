<?php

function hours_view_hours() {
	return t('This is a beautiful representation of what will become the <strong>Hour Table</strong> page.');
}

function hours_view_calendar($calData) {
	// fetch the data from the 'model'
	// (well, I'll be -- one CAN apply some semblance of MVP or MVC in a Drupal project)
	$calendarManager = CalendarManager::getInstance();
	$startTime = isset($calData['startTime']) ? $calData['startTime'] : time();
	$start_date = getDate($startTime);
	$now_date = getDate();
	$calendarManager->fetchMonth($calData['libId'], newApiCalendarService(), $startTime);
	
	$events = $calendarManager->getMonthEvents(TRUE);
	
	$page['title'] = array(
		'#type' => 'html_tag',
		'#tag' => 'h2',
		'#value' => t('Library Hours'),
	);
	$page['cal_header'] = array('#type' => 'container',
		'#attributes' => array('class' => 'cal_header'),
	);
	$page['cal_header']['prevmonth'] = array(
		'#type' => 'button',
		'#value' => t('<<'),
		'#attributes' => array(
			'class' => array('small green button3d'),
			'id' => 'prevmonth',
		),
	);
	$page['cal_header']['nextmonth'] = array(
		'#type' => 'button',
		'#value' => t('>>'),
		'#attributes' => array(
			'class' => array('small green button3d'),
			'id' => 'prevmonth',
		),
		'#ajax' => array(
			'event' => 'click',
			'callback' => 'hours_view_calendar_nextmonth',
		),
	);
	$page['cal_header']['heading'] = array(
		'#type' => 'html_tag',
		'#tag' => 'h3',
		'#value' => 'Library Hours',
	);	
	$page['hours_calendar'] = array(
		'#markup' => theme('hours_monthview',
			array(
				'events' => $events, 
				'start_date' => $start_date, 
				'now_date' => $now_date
			)
		)
	);
    $page['extra'] = array(
        '#type' => 'markup',
        '#markup' => t('You requested the ' . $calData['libId'] . ' library, which has the Google ID of ' . $calData['googleCalID']),
        '#prefix' => '<div>',
        '#suffix' => '</div>',
    );
    return $page;
}

function hours_day_form_callback($form, &$form_state) {
	$form['cal_email'] = array('#type' => 'textfield',
		'#value' => t('Enter email'),
		'#title' => t('Enter email'),
		'#ajax' => array(
			'callback' => 'hours_cal_email_callback',
			'wrapper' => 'cal_body',
		),
	);
	$form['cal_header'] = array(
		'#type' => 'container',
		'#attributes' => array('class' => array('cal_header')),
	);
	$form['cal_header']['prevmonth'] = array(
		'#type' => 'submit',
		'#value' => t('<<'),
		'#ajax' => array(
			'callback' => 'hours_view_calendar_prevmonth_callback',
			'wrapper' => 'cal_body',
			'name' => 'prevMonth',
		),
		'#attributes' => array('class' => array('button3d small green'),
			'id' => 'prevmonth',
		),
	);
	/*
	$form['cal_header']['nextmonth'] = array(
		'#type' => 'submit',
		'#value' => t('>>'),
		'#ajax' => array(
			'callback' => 'hours_view_calendar_nextmonth_callback',
			'wrapper' => 'cal_body',
			'name' => 'nextMonth',
		),
		'#attributes' => array('class' => array('button3d small green'),
			'id' => 'nextmonth',
		),
	);*/
	$form['cal_header']['heading'] = array(
		'#type' => 'html_tag',
		'#tag' => 'h3',
		'#value' => t('Value'),
	);
	$form['dinfo'] = array(
		'#markup' => '',
		'#prefix' => '<div>',
		'#suffix' => '</div>',
		'#attributes' => array('class'=>'day-info'),
	);
	$form['cal_body'] = array(
		'#type' => 'container',
		'#attributes' => array('id' => 'cal_body'),
	);
	$form['cal_body']['stuff'] = array(
		'#markup' => '<p>' . t('Simple text block here -- move on.') . '</p>',
	);
    return $form;
}

function hours_cal_email_callback($form, $form_state) {
	return $form['cal_email'];
}

function hours_view_calendar_nextmonth_callback($form, $form_state) {
	watchdog('hours_view_calendar_nextmonth', print_r(func_get_args(), TRUE));
	return t('Pretty, is it not?');
}

function hours_view_calendar_prevmonth_callback($form, $form_state) {
	$element = $form['cal_stuff']['stuff'];
	$element['#markup'] = 'Clicked "<<" button...';
	return $element;
}