<?php

define('CALENDAR_ID_TAIL', '@group.calendar.google.com');

require_once "inc/gapi/apiClient.php";
require_once "inc/gapi/contrib/apiCalendarService.php";

function newApiCalendarService()
{
	date_default_timezone_set('America/New_York');
	$apiClient = new apiClient();
	$apiClient->setUseObjects(true);
	$service = new apiCalendarService($apiClient);

	return $service;
}

/**
 * We use this function in 'CalendarManager::fetchMonth()'
 * if the PHP version doesn't support 'closures' (anonymous functions)
 */
function libCalFilter($var)
{
	return $var['libraryId'] == $GLOBALS['searchLibId'];
}

class CalendarManager
{
	public static $_instance = NULL;
	
	protected $_calendarMap = array();
	protected $_googleCalendarId = array();
	protected $_availableCalendars = array();
	protected $_sourceFile;
	protected $_defaultNumEvents = 7;
	protected $_calendarMode = 'week';
	protected $_lastStartTime = NULL;
	protected $_monthEvents = array();
	protected $_monthEventsHash = array();
	
	/**
	 * @Date array
	 * read-only
	 */
	private $_currentDate = NULL;
	
	/**
	 * Keep tabs of the previous start time
	 * when the "<< Prev" button is pressed
	 */
	private $_prevStartTime;
	
	/**
	 * same with the nextStartTime
	 */
	private $_nextStartTime;
	
	private $_startTime;
	
	private $_numEventsRequested;
	
	private function __construct($loadNow = FALSE)
	{
		$this->_sourceFile = drupal_get_path('modules', 'hours') . '/calendars.xml';
		if ($loadNow) {
			$this->readCalendarMap();
		}
		
		// initialize nextStartTime and prevStartTime
		$now = getDate();
		$now_timestamp = mktime(0, 0, 0, $now['mon'], $now['mday'], $now['year']);
		$this->_currentDate = $now;
		
		if ($this->_calendarMode == 'week') {
			// determine actual date of 'Sunday' from now
			$delta_day = (int) date('w', $now_timestamp);
			$startTime = $now_timestamp - (86400 * $delta_day);
			$endTime = $now_timestamp + ((86400 * ($this->_defaultNumEvents - $delta_day)) - 1);
		} else {
			$startTime = $now_timestamp;
			$endTime = $now_timestamp + ((86400 * $this->_defaultNumEvents) - 1);
		}
		$this->_startTime = $now_timestamp;
		//echo sprintf("determined start time to be '%d'\n", $this->_startTime);
		$this->_nextStartTime = $endTime + 1;
		$this->_prevStartTime = $startTime - (86400 * 7);
	}
	
	public static function getInstance($sourceFile = NULL) {
		if (!self::$_instance) {
			self::$_instance = new CalendarManager(FALSE);
			if (isset($sourceFile)) {
				self::$_instance->sourceFile = $sourceFile;
			}
			self::$_instance->readCalendarMap();
		}
		return self::$_instance;
	}
		
	public static function newCalendarManager($sourceFile)
	{
		$obj = new CalendarManager(FALSE);
		$obj->sourceFile = $sourceFile;
		$obj->readCalendarMap();
		return $obj;
	}
	
	public function __set($key, $value)
	{
		$method = 'set' . ucfirst($key);
		if (array_key_exists($key, $this->_calendarMap)) {
			$this->_calendarMap[$key] = $value;
			return $this;
		} else {
			if (!method_exists($this, $method)) {
				throw new Exception('Invalid property for "CalendarManager".');
			}
			return $this->$method($value);
		}
	}
	
	public function setCalendarMode($mode)
	{
		$this->_calendarMode = (string) $mode;
		return $this;
	}
	
	public function setDefaultNumEvents($n)
	{
		$this->_defaultNumEvents = $n;
		return $this;
	}
		
	public function setNextStartTime($time)
	{
		$this->_nextStartTime = $time;
		return $this;
	}
	
	public function setPrevStartTime($time)
	{
		$this->_prevStartTime = $time;
		return $this;
	}
	
	public function setSourceFile($file)
	{
		$this->_sourceFile = $file;
		return $this;
	}
	
	public function __get($key)
	{
		$method = 'get' . ucfirst($key);	
		if ('hours' == $key) {
			return $this->getHours();
		}
		if (array_key_exists($key, $this->_calendarMap)) {
			return $this->_calendarMap[$key];
		}
		if (!method_exists($this, $method)) {
			throw new Exception('Invalid property (' . $key . ') for "CalendarManager".');
		}
		return $this->$method();
	}

	public function getAvailableCalendars()
	{
		return $this->_availableCalendars;
	}
	
	public function getCalendarMode()
	{
		return $this->_calendarMode;
	}
	
	public function getCurrentDate()
	{
		return $this->_currentDate;
	}
	
	public function getDefaultNumEvents()
	{
		#throw new Exception($this->_defaultNumEvents);
		return $this->_defaultNumEvents;
	}
	
	public function getGoogleCalendarIdForLibId($libId) {
		if (isset($this->_googleCalendarId[$libId])) {
			return $this->_googleCalendarId[$libId];
		}
		return NULL;
	}
	
	public function getHours()
	{
		$return = array(
			'nextStartTime' => $this->_nextStartTime,
			'prevStartTime' => $this->_prevStartTime,
			'table' => array(),
			'assocTable' => array(),
		);
		foreach ($this->_calendarMap as $calId => $c) {
            if (!isset($c['hoursData'])) {
                continue;
            }
			$return['table'][] = array(
				'calendarId' => $calId,
				'libraryName' => $c['title'],
				'hoursData' => $c['hoursData'],
			);
			$return['assocTable'][$c['id']] = array(
				'calendarId'	=> $calId,
				'libraryName'	=> $c['title'],
				'hoursData'		=> $c['hoursData'],
			);
		}
		return $return;
	}
	
	public function getMonthEvents($fromHash = FALSE)
	{
		if ($fromHash == FALSE) {
			return $this->_monthEvents;
		}
		$keys = array_keys($this->_monthEventsHash);
		sort($keys, SORT_NUMERIC);
		$r = array();
		foreach ($keys as $key) {
			$r[] = $this->_monthEventsHash[$key];
		}
		return $r;
	}
	
	public function getNextStartTime()
	{
		return $this->_nextStartTime;
	}
	
	public function getNumEventsRequested()
	{
		return $this->_numEventsRequested;
	}
	
	public function getPageData()
	{
		$headers = array();
		$rows = array();
		foreach ($this->_calendarMap as $calId => $data) {
			$libRow = array();
			$hoursData = $data['hoursData'];
			foreach ($hoursData as $h) {
				if (sizeof($headers) < sizeof($hoursData)) {
					$headers[] = array(
						'theDate' => $h->libraryDate['longDay'] . '<br />' 
							. $h->libraryDate['dateStr'],
						'currentDay' => $h->isCurrentDay)
					;
				}
				$libRow[] = array(
					'hours'		=> $h->hours,
					'currentDay'=> $h->isCurrentDay,
				);
			}
			#$rows[] = $libRow;
			$rows[] = array(
				'calId' => $calId,
				'libraryId' => $data['id'],
				'rowData' => $libRow,
			);
		}
		$headerTitle = date('l, F j', $this->_startTime) . ' - ' . date('l, F j', $this->_endTime);
		$arr = array(
			'headers'	=> $headers,
			'rows'		=> $rows,
			'lastStartTime'	=> $this->_lastStartTime,
			'prevStartTime' => $this->_prevStartTime,
			'nextStartTime' => $this->_nextStartTime,
			'currentDate'	=> $this->_currentDate,
			'headerTitle'	=> $headerTitle,
		);
		return $arr;
	}
	
	public function getPrevStartTime()
	{
		return $this->_prevStartTime;
	}
	
	public function getStartTime()
	{
		return $this->_startTime;
	}
	
	public function fetchMonth($libId, $service, $startTime)
	{
		# what month are we in...?
		$dArr = explode('|', date('n|Y', $startTime));
		$month = $dArr[0];
		$year = $dArr[1];
		
		# how about the number of days?
		$numDaysInMonth = (int) date('t', $startTime);
		
		if ((int) date('j', $startTime) != 1) {
			$firstDayOfMonth = mktime(0, 0, 0, $month, 1, (int) date('Y', $startTime));
		} else {
			$arr = getDate($startTime);
			$firstDayOfMonth = mktime(0, 0, 0, $arr['mon'], $arr['mday'], $arr['year']);
		}
		$lastDayOfMonth = mktime(23, 59, 59, $month, $numDaysInMonth, $year);
		
		# when is the first Sunday
		$firstSunday = $firstDayOfMonth - (86400 * (int)date('w', $firstDayOfMonth));
		$lastSaturday = $lastDayOfMonth + ((6 - (int)date('w', $lastDayOfMonth)) * 86400);

		// MODIFIED to perform timestamp (second) math
		$numEvents = (int) ((($lastSaturday - $firstSunday) + 1) / 86400);
		
		//echo sprintf("First Sunday = [%s]; Last Saturday is [%s]<br />\n", 
		//	date('M j, Y', $firstSunday), date('M j, Y', $lastSaturday));
		
		$params = array(
			'timeMin' => date('Y-m-d', $firstSunday) . 'T00:00:00-05:00',
			'singleEvents' => true,
			'orderBy' => 'startTime',
			'maxResults' => $numEvents,
		);
		// find the calendarID for libId
		$fn = function($var)
		{
			return $var['libraryId'] == $GLOBALS['searchLibId'];
		};
		$GLOBALS['searchLibId'] = $libId;
		// Can we use the 'closure' feature?
		if (version_compare(PHP_VERSION, '5.3.0') >= 0) {
    		$z = array_filter($this->availableCalendars, $fn);
		} else {
			$z = array_filter($this->availableCalendars, 'libCalFilter');
		}
		#$z = array_filter($this->availableCalendars, $fn);
		$entry = array_pop($z);
		$calId = $entry['calId'];
		
		$events = $service->events->listEvents($calId . CALENDAR_ID_TAIL, $params);

		$monthEvents = array();
		#$thisWeek = array();
		foreach ($events->items as $eventItem) {
			$eventObject = $this->_event_fc_object($eventItem);
			$key = mktime(0, 0, 0, 
				$eventObject->start_date['mon'],
				$eventObject->start_date['mday'],
				$eventObject->start_date['year']);
			$this->_monthEvents[] = $eventObject;
			if (!isset($this->_monthEventsHash[$key])) {
				$this->_monthEventsHash[$key] = $eventObject;
			} else {
				// if what is stored there now is "CLOSED" then ignore
				if (preg_match('/closed/i', $this->_monthEventsHash[$key]->summary) == 0) {
					$this->_monthEventsHash[$key] = $eventObject;
				}
			}
		}
	}
	
	/**
	 * Alias to new 'fetchWeek'
	 */
	public function fetchHours($options, $service, $now = NULL)
	{
		$this->fetchWeek($options, $service, $now);
	}

    /**
     * Fetchs Google calendar data for all applicable
     * Duke library calendar feeds.
     *
     * @param $variables
     *   An associative array containing (but not limited to):
     *   - firstDay
     *   - numEvents
     *   - limitLibraries => array of libraries to query
     */
	public function fetchWeek($options, $service, $now = NULL)
	{
		if ($now == NULL) {
			$now = getDate();
		} else {
			# accept whatever date is supplied by the front end
			$now = getDate($now);
		}
		$now_timestamp = mktime(0, 0, 0, $now['mon'], $now['mday'], $now['year']);
		$this->_currentDate = getDate();
		
		$this->_lastStartTime = array(
			'timestamp'		=> $now,
			'dateStr'		=> date('D n/j', $now_timestamp),
		);
		
		$startTime = '';	// TBD.
		$endTime = '';		// TBD
		
		$firstDay = array_key_exists('firstDay', $options) 
			? $options['firstDay'] 
			: 'Sunday';
		
		$numEvents = array_key_exists('numEvents', $options)
			? (int) $options['numEvents']
			: (($firstDay == 'Sunday') ? 7 : $this->_defaultNumEvents);
			
		if ('Sunday' == $firstDay) {
			// determine actual date of 'Sunday' from now
			$delta_day = (int) date('w', $now_timestamp);
			$startTime = $now_timestamp - (86400 * $delta_day);
			$endTime = $now_timestamp + ((86400 * ($numEvents - $delta_day)) - 1);
		} else {
			$startTime = $now_timestamp;
			$endTime = $now_timestamp + ((86400 * $numEvents) - 1);
		}
		$this->_nextStartTime = $endTime + 1;
		$this->_prevStartTime = $startTime - (86400 * 7);
		
		$params = array(
			'timeMin' => date('Y-m-d', $startTime) . 'T00:00:00-05:00',
			'singleEvents' => true,
			'orderBy' => 'startTime',
			'maxResults' => $numEvents,
		);
			
		$hasSelection = (array_key_exists('libraries', $options) && count($options['libraries']));
		foreach ($this->_calendarMap as $calId => $calMapData) {
			$bool = true;
			if ($hasSelection) {
				if (!in_array($calMapData['id'], $options['libraries'])) {
					$bool = false;
				}
			}
			if ($bool) {
				$events = $service->events->listEvents($calId . CALENDAR_ID_TAIL, $params);
				foreach ($events->items as $eventItem) {
					if (!array_key_exists('hoursData', $this->_calendarMap[$calId])) {
						$this->_calendarMap[$calId]['hoursData'] = array();
					}
					$this->_calendarMap[$calId]['hoursData'][] = 
                        $this->_event_date_object($eventItem, $calMapData['title']);
				}
			}
		}
	}
	
	protected function _event_fc_object($eventItem)
	{
		$o = new StdClass();
		$tmp = $this->_event_date_object($eventItem, NULL);
		
		$o->title = $tmp->hours;
		$o->summary = $eventItem->summary;
		$o->allDay = $tmp->allDay;
		$o->start = $tmp->timestamp;
		$o->start_date = getdate($o->start);
		$o->libraryClosed = $tmp->libraryClosed;
		if (isset($tmp->end)) {
			$o->end = $tmp->end;
			$o->end_date = getdate($o->end);
		}
		$o->removeAllDayCssClass = $tmp->removeAllDayCssClass;
		return $o;
	}
	
	protected function _event_date_object($eventItem, $libraryName)
	{		
		$object = new StdClass();
		$object->allDay = FALSE;
		$object->removeAllDayCssClass = FALSE;
		$object->libraryClosed = FALSE;
		
		if (isset($eventItem->start->dateTime)) {
			$convertedTime = strtotime($eventItem->start->dateTime);
		} else {
			$convertedTime = strtotime($eventItem->start->date);
		}
		
		$object->isCurrentDay = ((int) date('z', $convertedTime) == (int) $this->_currentDate['yday']);
		$object->libraryDate = array(
			'dayAndDate' => date('D n/j', $convertedTime),
			'shortDay' => date('D', $convertedTime),
			'longDay' => date('l', $convertedTime),
			'dateStr' => date('n/j', $convertedTime),
			'wday' => (int)date('w', $convertedTime),
			'yday' => (int)date('z', $convertedTime),
		);
		$object->timestamp = $convertedTime;
			
		// the summary format for Perkins includes "Perkins: some hour criteria"
		if (preg_match('/^(lilly|public|rubenstein|perkins|music|lsc):/i', $eventItem->summary) == 1) {
			$object->hours = preg_replace('/^(lilly|public|rubenstein|perkins|music|lsc): /i', '', $eventItem->summary);
			$object->hours = str_replace('-', ' &ndash; ', $object->hours);
			$object->allDay = preg_match('/24 hours/i', $object->hours) == 1;
			$object->removeAllDayCssClass = !$object->allDay;
		} else if (preg_match('/closed/i', $eventItem->summary) == 1) {
			$object->hours = 'CLOSED';
			$object->allDay = TRUE;
			$object->libraryClosed = TRUE;
		} else if (isset($eventItem->start->dateTime)) {
			$startDateTime = strtotime($eventItem->start->dateTime);
			$endDateTime = strtotime($eventItem->end->dateTime);
			$object->start = $startDateTime;
			$object->end = $endDateTime;
		
			if (preg_match('/24 hours/i', $eventItem->summary) == 1) {
				$object->hours = 'Open 24 hours';
				$object->allDay = TRUE;
			} else if (date('i', $endDateTime) == '59' && date('D', $endDateTime) == 'Sun') {
				// we need to account for the special case when the 
				// end date is actually 23:59
				// set the 'Hours' attribute to 'Open at <startTime>'
				$object->hours = 'Open at ' . date('ga', $startDateTime);
			} else {        
				$_start = date('i', $startDateTime) == '00'
					? date('ga', $startDateTime)
					: date('g:ia', $startDateTime);
				$_end = date('i', $endDateTime) == '00'
					? date('ga', $endDateTime)
					: date('g:ia', $endDateTime);
				$object->hours = $_start . ' - ' . $_end;   
			}
			$object->removeAllDayCssClass = TRUE;
		} else {
			// we have a date
			$startDate = strtotime($eventItem->start->date);
			
			if (date('D', $startDate) == 'Fri') {
				$object->hours = 'Closes at Midnight';
				$object->allDay = TRUE;
			} else {
				$object->hours = 'Open 24 Hours';
				$object->allDay = TRUE;
			}
			$object->removeAllDayCssClass = TRUE;
		}
		return $object;
	}
	
	public function readCalendarMap()
	{
		try {
			$file_contents = file_get_contents($this->_sourceFile);
			$xml = new SimpleXMLElement($file_contents);
			foreach ($xml->children() as $calendar) {
				$newKey = (string) $calendar['id'];
				$this->_availableCalendars[] = array(
					'libraryName'	=> (string) $calendar->libraryName,
					'libraryId'		=> (string) $calendar->libraryId,
					'calId'			=> $newKey
				);
				$this->_calendarMap[$newKey] = array(
					'title' => (string) $calendar->libraryName,
					'id'	=> (string) $calendar->libraryId,
				);
				$this->_googleCalendarId[(string) $calendar->libraryId] = $newKey;
				#$this->_calendarMap[$newKey] = (string) $calendar->libraryName;
			}
		} catch (Exception $e) {
			echo $e->getMessage();
		}
	}
}

?>
