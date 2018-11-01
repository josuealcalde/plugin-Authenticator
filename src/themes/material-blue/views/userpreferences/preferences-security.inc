<?php
/**
 * @var \SP\Core\UI\ThemeIcons $icons
 * @var \SP\Config\ConfigData  $configData
 * @var callable               $_getvar
 * @var \SP\Mvc\View\Template  $this
 */

$chk2FAEnabled = $_getvar('chk2FAEnabled');
?>

<div id="title" class="titleNormal">
    <i class="material-icons">vpn_key</i>
    <?php echo _t('authenticator', 'Autentificación'); ?>
</div>

<form method="post" name="frmSecurity" id="frmSecurity" class="form-action"
      data-onsubmit="twofa/save"
      data-plugin="Authenticator"
      data-action-route="<?php echo $_getvar('route'); ?>"
      data-hash="">

    <table id="tblSite" class="data tblConfig round">
        <tr>
            <td class="descField">
                <?php echo _t('authenticator', 'Autentificación en 2 pasos'); ?>
                <div id="help-2fa"
                     class="icon material-icons <?php echo $icons->getIconHelp()->getClass(); ?>"><?php echo $icons->getIconHelp()->getIcon(); ?></div>
                <div class="mdl-tooltip mdl-tooltip--large" for="help-2fa">
                    <p>
                        <?php echo _t('authenticator', 'Habilita la autentificación en 2 pasos que requiere de la introducción de un token generado por una aplicación como Google Authenticator.'); ?>
                    </p>

                    <p>
                        <?php echo _t('authenticator', 'Escanee el código QR proporcionado y a continuación introduzca la clave de 6 dígitos.'); ?>
                    </p>
                </div>
            </td>
            <td class="valField">
                <label class="mdl-switch mdl-js-switch mdl-js-ripple-effect" for="2faenabled">
                    <input type="checkbox" id="2faenabled"
                           class="mdl-switch__input mdl-color-text--indigo-400"
                           name="2faenabled" <?php echo $_getvar('chk2FAEnabled') ? 'checked' : ''; ?>/>
                    <span class="mdl-switch__label"><?php echo _t('authenticator', 'Activar'); ?></span>
                </label>

                <div id="qr_code_wrapper">
                    <?php
                    $qrCode = $_getvar('qrCode');

                    if (!$chk2FAEnabled && $qrCode): ?>
                        <div id="qr_code">
                            <img id="qrcode" src="data:image/gif;base64,<?php echo $qrCode; ?>" alt="QR Code"/>
                        </div>
                    <?php elseif ($qrCode === false): ?>
                        <p class="ui-state-error"><?php echo _t('authenticator', 'Error al obtener el código QR. Inténtelo de nuevo'); ?></p>
                    <?php endif; ?>

                    <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                        <input id="pin" name="pin" type="text"
                               pattern="([0-9]{6}|[0-9a-f]{20})"
                               class="mdl-textfield__input mdl-color-text--indigo-400"
                               maxlength="20"
                               required/>
                        <label class="mdl-textfield__label"
                               for="security_pin"><?php echo _t('authenticator', 'Código'); ?></label>
                    </div>

                    <div id="2fa_warning">
                        <div class="icon material-icons <?php echo $icons->getIconWarning()->getClass(); ?>"><?php echo $icons->getIconWarning()->getIcon(); ?></div>
                        <?php echo _t('authenticator', 'Una vez activada, sólo es posible acceder si se dispone del dispositivo generador de códigos asociado.'); ?>
                    </div>
                </div>
            </td>
        </tr>
        <tr>
            <td class="descField"><?php echo _t('authenticator', 'Días Caducidad'); ?></td>
            <td class="valField">
                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                    <input id="expiredays" name="expiredays" type="number" step="1"
                           min="0" max="720" class="mdl-textfield__input mdl-color-text--indigo-400"
                           value="<?php echo $_getvar('expireDays') ?: 90; ?>" required/>
                    <label class="mdl-textfield__label"
                           for="expiredays"><?php echo _t('authenticator', 'Días'); ?></label>
                </div>
            </td>
        </tr>

        <?php if ($chk2FAEnabled): ?>
            <tr>
                <td class="descField">
                    <?php echo _t('authenticator', 'Códigos Recuperación'); ?>
                    <i class="btn-action material-icons"
                       title="<?php echo _t('authenticator', 'Ver códigos'); ?>"
                       data-onclick="twofa/viewRecoveryCodes"
                       data-plugin="Authenticator"
                       data-action-route="<?php echo $_getvar('viewCodesRoute'); ?>"
                       data-dst-id="#recovery-codes">remove_red_eye</i>
                </td>
                <td class="valField" id="recovery-codes" style="display: none;">
                    <div class="list-wrap"></div>
                </td>
            </tr>
        <?php endif; ?>
    </table>

    <input type="hidden" name="isAjax" value="1"/>
    <input type="hidden" name="sk" value="">
</form>

<div class="tab-actions">
    <ul>
        <li>
            <button form="frmSecurity"
                    class="mdl-button mdl-js-button mdl-button--fab mdl-button--mini-fab mdl-button--colored <?php echo $icons->getIconSave()->getClassButton(); ?>"
                    title="<?php echo $icons->getIconSave()->getTitle(); ?>">
                <i class="material-icons"><?php echo $icons->getIconSave()->getIcon(); ?></i>
            </button>
        </li>
    </ul>
</div>