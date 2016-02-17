<?php
/**
 * @file
 * This file includes page callbacks for Meds reports module.
 */

/**
 * Performance center page callback.
 */
function performance_test_page_callback($form, $form_state, $current_category) {
  $context = array('context' => PERFORMANCE_TEST_TRANSLATE_CONTEXT);
  $output = '';

  drupal_set_title(t('Drupal Performance center', array(), $context));

  // Get all performance test plugins.
  $tests      = performance_test_get_test_plugins();
  $categories = performance_test_get_available_categories();

  foreach ($categories as $category) {
    if ($category['type_name'] == $current_category) {
      $form['title'] = array(
        '#markup' => '<h2>' . $category['page_title'] . '</h2>',
      );
    }
    continue;
  }

  $t = get_t();
  if (!empty($tests)) {
    foreach ($tests as $test) {
      // Create an instance for the plugin.
      $plugin = PerformanceTestManager::factory($test);
      $test_category = $plugin->testCategory();

      // Move to the next test plugin if current has wrong category.
      if ($current_category != $test_category) {
        continue;
      }

      $class = $test['handler']['class'];
      if (!isset($form[$current_category])) {
        $form[$class] = array(
          '#type' => 'fieldset',
          '#title' => $t($test['name'], array(), $context),
          '#collapsible' => TRUE,
          '#collapsed'   => FALSE,
        );
      }

      // Add form elements.
      $iterations = !empty($plugin->iterations) ? $plugin->iterations : PERFORMANCE_TEST_ITERATIONS;
      $callbacks  = $plugin->exportResults();
      $output = array();
      foreach ($callbacks as $callback) {
        if (is_callable(array($plugin, $callback))) {
          performance_test_start_timer_for_variant($callback);
          $callback_data = $plugin->$callback($iterations);
          performance_test_read_timer_for_variant($callback_data, $callback);

          $output[] = $callback_data;
        }
      }

      $output = performance_test_render_plugin_results($output, $test['name']);
      if (!empty($output)) {
        $form[$class]['data'] = array(
          '#markup' => $output,
        );
      }
    }
  }

  return $form;
}

/**
 * Render results of code execution.
 */
function performance_test_render_plugin_results($output, $callback) {

/*  define('CHART_TYPE_LINE', 'lc');
  define('CHART_TYPE_LINE_NO_AXIS', 'ls');
  define('CHART_TYPE_LINE_XY', 'lxy');
  define('CHART_TYPE_BAR_H', 'bhs');
  define('CHART_TYPE_BAR_V', 'bvs');
  define('CHART_TYPE_BAR_H_GROUPED', 'bhg');
  define('CHART_TYPE_BAR_V_GROUPED', 'bvg');
  define('CHART_TYPE_PIE', 'p');
  define('CHART_TYPE_PIE_3D', 'p3');
  define('CHART_TYPE_PIE_CONCENTRIC', 'pc');
  define('CHART_TYPE_VENN', 'v');
  define('CHART_TYPE_SCATTER', 's');
  define('CHART_TYPE_MAP', 't');
  define('CHART_TYPE_RADAR', 'r');
  define('CHART_TYPE_RADAR_FILLED', 'rs');
  define('CHART_TYPE_GMETER', 'gom');
  define('CHART_TYPE_QR', 'qr');*/

  $chart = array(
    '#chart_id' => $callback,
    '#title'    => chart_title($callback, 'cc0000', 15),
    '#type'     => CHART_TYPE_PIE_3D,
    '#size'     => chart_size(PERFORMANCE_TEST_CHART_SIZE_WIDTH, PERFORMANCE_TEST_CHART_SIZE_HEIGHT),
  );

  $suffix = ' ' . t('Sec', array(), performance_test_get_context());
  foreach ($output as $data) {
    $chart['#data'][] = $data['time'];
    $chart['#labels'][] = $data['title'] . ' ' . round($data['time'], 2) . $suffix;
  }

  return theme('chart', array('chart' => $chart));
}
